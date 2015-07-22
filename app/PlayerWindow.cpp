#include <QtWidgets>
#include "PlayerWindow.h"
#include "Settings.h"

using namespace fMusic::App;

/**
 * Constants
 */
const QSize PlayerWindow::DEFAULT_SIZE = QSize(600, 400);
const QPoint PlayerWindow::DEFAULT_POS = QPoint(20, 20);
const char *PlayerWindow::DEFAULT_SONG = "function f(t)\n"
                                         "\tif (t % 300) == 0 then\n"
                                         "\t\treturn 144, (math.sin(t % math.pi) * 26) + 48, 70\n"
                                         "\tend\n"
                                         "\treturn 0, 0, 0\n"
                                         "end";

/**
 * Create player/editor window
 */
PlayerWindow::PlayerWindow()
    : QMainWindow(),
      logWindow(new LogWindow()),
      visualiserWindow(new VisualiserWindow(logWindow)),
      player(logWindow),
      midi(new fMusic::Core::Instruments::MIDI(logWindow)),
      playIcon(":/play.svg"),
      pauseIcon(":/pause.svg"),
      newAction(QIcon(":/new.svg"), tr("&New"), this),
      openAction(QIcon(":/open.svg"), tr("&Open..."), this),
      saveAction(QIcon(":/save.svg"), tr("&Save"), this),
      saveAsAction(tr("Save &As..."), this),
      playAction(this),
      stopAction(QIcon(":/stop.svg"), tr("S&top"), this),
      settingsAction(tr("Preferences"), this),
      closeAction(tr("&Close"), this),
      highlighter(textEdit.document()) {

    // Show log window
    logWindow->show();

    // Show visualiser window
    player.addInstrument(visualiserWindow);
    visualiserWindow->show();

    // Initialise MIDI
    player.addInstrument(midi);

    // Window configuration
    setUnifiedTitleAndToolBarOnMac(true);
    setCentralWidget(&textEdit);

    // Window geometry
    Settings settings;
    settings.beginGroup("PlayerWindow");
    resize(settings.value("size", DEFAULT_SIZE).toSize());
    move(settings.value("pos", DEFAULT_POS).toPoint());

    // Actions
    setPlayAction();

    newAction.setShortcuts(QKeySequence::New);
    newAction.setStatusTip(tr("Create a new song"));
    connect(&newAction, SIGNAL(triggered()), this, SLOT(newSong()));

    openAction.setShortcuts(QKeySequence::Open);
    openAction.setStatusTip(tr("Open an existing song"));
    connect(&openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction.setShortcuts(QKeySequence::Save);
    saveAction.setStatusTip(tr("Save the song to disk"));
    connect(&saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction.setShortcuts(QKeySequence::SaveAs);
    saveAsAction.setStatusTip(tr("Save the song under a new name"));
    connect(&saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    playAction.setStatusTip(tr("Play song"));
    connect(&playAction, SIGNAL(triggered()), this, SLOT(play()));

    stopAction.setStatusTip(tr("Stop playing"));
    connect(&stopAction, SIGNAL(triggered()), this, SLOT(stop()));

    settingsAction.setShortcuts(QKeySequence::Preferences);
    settingsAction.setStatusTip(tr("Preferences"));
    connect(&settingsAction, SIGNAL(triggered()), &settingsWindow, SLOT(show()));

    closeAction.setStatusTip(tr("Close this window"));
    connect(&closeAction, SIGNAL(triggered()), this, SLOT(close()));

    // File menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(&newAction);
    fileMenu->addAction(&openAction);
    fileMenu->addAction(&saveAction);
    fileMenu->addAction(&saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(&settingsAction);
    fileMenu->addAction(&closeAction);

    // Play menu
    playMenu = menuBar()->addMenu(tr("&Play"));
    playMenu->addAction(&playAction);
    playMenu->addAction(&stopAction);

    // Toolbar
    toolbar = addToolBar(tr("File"));
    toolbar->setIconSize(QSize(22, 22));
    toolbar->addAction(&newAction);
    toolbar->addAction(&openAction);
    toolbar->addAction(&saveAction);
    toolbar->addSeparator();
    toolbar->addAction(&playAction);
    toolbar->addAction(&stopAction);

    // Text widget font
    font.setFamily("Menlo");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);
    textEdit.setFont(font);

    // Text widget tab width
    QFontMetrics metrics(font);
    textEdit.setTabStopWidth(4 * metrics.width(' '));

    // Status bar
    statusBar()->showMessage(tr("Ready"));

    // Start with blank document
    setCurrentSong("");
    textEdit.setPlainText(DEFAULT_SONG);

}

/**
 * Save song file when window is closed
 */
void PlayerWindow::closeEvent(QCloseEvent *event) {
    if (saveIfModified()) {
        // Save window size and position
        Settings settings;
        settings.beginGroup("PlayerWindow");
        settings.setValue("size", size());
        settings.setValue("pos", pos());
        settings.endGroup();

        // Quit
        event->accept();
    } else {
        // Ignore if user cancelled
        event->ignore();
    }
}

/**
 * Create blank song document
 */
void PlayerWindow::newSong() {
    if (saveIfModified()) {
        textEdit.clear();
        setCurrentSong("");
    }
}

/**
 * Open existing song file
 */
void PlayerWindow::open() {
    if (saveIfModified()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            loadSong(fileName);
        }
    }
}

/**
 * Save current song document
 */
bool PlayerWindow::save() {
    if (curSong.isEmpty()) {
        return saveAs();
    } else {
        return saveSong(curSong);
    }
}

/**
 * Save current song document with a new filename
 */
bool PlayerWindow::saveAs() {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList files;
    if (dialog.exec()) {
        files = dialog.selectedFiles();
    } else {
        return false;
    }

    return saveSong(files.at(0));
}

/**
 * Play current song document
 */
void PlayerWindow::play() {
    if (player.isPlaying()) {
        // Pause
        player.pause();
    } else {
        // Set player settings
        Settings settings;
        settings.beginGroup("Player");
        player.setInterval(settings.value("interval", fMusic::Core::Player::DEFAULT_INTERVAL).toInt());

        // Play
        player.play(textEdit.toPlainText().toUtf8().constData());
    }
    setPlayAction();
}

/**
 * Stop playing current song
 */
void PlayerWindow::stop() {
    player.stop();
    setPlayAction();
}

/**
 * Set state of play/pause toolbar button and menu item
 */
void PlayerWindow::setPlayAction() {
    if (player.isPlaying() && !player.isPaused()) {
        playAction.setIcon(pauseIcon);
        playAction.setText(tr("&Pause"));
    } else {
        playAction.setIcon(playIcon);
        playAction.setText(tr("&Play"));
    }
}

/**
 * Set current song
 */
void PlayerWindow::setCurrentSong(const QString &fileName) {
    curSong = fileName;
    textEdit.document()->setModified(false);
    setWindowModified(false);

    setWindowFilePath((curSong.isEmpty()) ? "untitled.fmu" : curSong);
}

/**
 * Load a song file
 */
void PlayerWindow::loadSong(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        const QString text = tr("Cannot read song %1:\n%2.").arg(fileName).arg(file.errorString());
        QMessageBox::warning(this, tr("Application"), text);
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit.setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentSong(fileName);
    statusBar()->showMessage(tr("Song loaded"), 2000);
}

/**
 * Save a song file
 */
bool PlayerWindow::saveSong(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        const QString text = tr("Cannot write song %1:\n%2.").arg(fileName).arg(file.errorString());
        QMessageBox::warning(this, tr("Application"), text);
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit.toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentSong(fileName);
    statusBar()->showMessage(tr("Song saved"), 2000);
    return true;
}

/**
 * If current song document has been modified, show save/discard dialog
 */
bool PlayerWindow::saveIfModified() {
    if (textEdit.document()->isModified()) {
        const QString text = tr("The song has been modified. Do you want to save your changes?");
        QMessageBox::StandardButtons buttons = QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel;
        QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Application"), text, buttons);
        if (ret == QMessageBox::Save) {
            return save();
        } else if (ret == QMessageBox::Cancel) {
            return false;
        } else {
            textEdit.document()->setModified(false);
        }
    }
    return true;
}
