#include <QMenuBar>
#include "LogWindow.h"

using namespace EvoMu::App;

/**
 * Create log window
 */
LogWindow::LogWindow(AppLog *log)
    : QMainWindow(),
      clearAction(tr("C&lear..."), this),
      closeAction(tr("&Close"), this) {

    // Window configuration
    setWindowIconText(tr("Log"));
    setCentralWidget(&text);
    setGeometry(20, 480, 800, 200);

    // Log
    connect(log, &AppLog::write, this, &LogWindow::append);

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
