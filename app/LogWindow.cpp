#include <iostream>
#include <sstream>
#include <QDateTime>
#include <QMenuBar>
#include "LogWindow.h"

using namespace EvoMu::App;

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
    setGeometry(20, 480, 800, 200);

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

const char *logStatusName[] = {"error", "warn", "info", "debug"};

/**
 * Format log message and send "write" signal
 */
void LogWindow::message(EvoMu::Core::LogStatus status, const std::string &message) {
    // Get current date and time
    QDateTime dateTime(QDateTime::currentDateTime());
    std::string dateTimeStr = dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz").toStdString();

    // Format as "[<timestamp>][<status>] message"
    std::ostringstream out;
    out << '[' << dateTimeStr << "][" << logStatusName[(int)status] << "] " << message;

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
