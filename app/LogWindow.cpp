#include <iostream>
#include <sstream>
#include <QDateTime>
#include <QMenuBar>
#include "LogWindow.h"
#include "Settings.h"

using namespace fMusic::App;

/**
 * Constants
 */
const QSize LogWindow::DEFAULT_SIZE = QSize(800, 200);
const QPoint LogWindow::DEFAULT_POS = QPoint(20, 480);
const char *LogWindow::LOG_STATUS_NAMES[] = {"error", "warn", "info", "debug"};

/**
 * Create log window
 */
LogWindow::LogWindow()
    : QMainWindow(),
      clearAction(tr("C&lear..."), this),
      closeAction(tr("&Close"), this) {

    // Window configuration
    setWindowIconText(tr("Log"));
    setCentralWidget(&text);

    // Window geometry
    Settings settings;
    settings.beginGroup("LogWindow");
    resize(settings.value("size", DEFAULT_SIZE).toSize());
    move(settings.value("pos", DEFAULT_POS).toPoint());

    // Log
    connect(this, &LogWindow::write, this, &LogWindow::append);

    // Actions
    clearAction.setShortcuts(QKeySequence::New);
    clearAction.setStatusTip(tr("Clear the log"));
    connect(&clearAction, SIGNAL(triggered()), this, SLOT(clear()));

    closeAction.setStatusTip(tr("Close this window"));
    connect(&closeAction, SIGNAL(triggered()), this, SLOT(close()));

    // File menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(&clearAction);
    fileMenu->addAction(&closeAction);

    // Text widget colour palette
    palette.setColor(QPalette::Base, QColor::fromRgb(0,0,0));
    palette.setColor(QPalette::Text, QColor::fromRgb(255,255,255));

    // Text widget format
    format.setFontFamily("Menlo");
    format.setFontPointSize(11);

    // Text widget configuration
    text.setPalette(palette);
    text.setCurrentCharFormat(format);
    text.setTabStopWidth(200);
    text.setReadOnly(true);
}

/**
 * Format log message and send "write" signal
 */
void LogWindow::message(fMusic::Core::LogStatus status, const std::string &message) {
    // Get current date and time
    QDateTime dateTime(QDateTime::currentDateTime());
    std::string dateTimeStr = dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz").toStdString();

    // Format as "[<timestamp>][<status>] message"
    std::ostringstream out;
    out << '[' << dateTimeStr << "][" << LOG_STATUS_NAMES[(int)status] << "] " << message;

    emit write(QString(out.str().c_str()));
}

/**
 * Append log message to window
 */
void LogWindow::append(QString str) {
    text.appendPlainText(str);
}

/**
 * Clear log window
 */
void LogWindow::clear() {
    text.setPlainText("");
}

/**
 * Save window settings on close
 */
void LogWindow::closeEvent(QCloseEvent *event) {
    // Save window size and position
    Settings settings;
    settings.beginGroup("LogWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    // Quit
    event->accept();
}
