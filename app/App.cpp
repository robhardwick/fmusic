#include "App.h"

using namespace EvoMu::App;

App::App(int &argc, char *argv[])
    : QApplication(argc, argv),
      exitAction(this),
      logWindow(new LogWindow()),
      visualiserWindow(new VisualiserWindow(logWindow)),
      playerWindow(logWindow, visualiserWindow) {

    // App configuratiom
    setOrganizationName("EvoMu");
    setApplicationName("EvoMu");

    // Quit application signal
    exitAction.setShortcuts(QKeySequence::Quit);
    connect(&exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    // Show log, visualiser and player windows
    logWindow->show();
    visualiserWindow->show();
    playerWindow.show();
}
