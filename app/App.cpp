#include "App.h"

using namespace EvoMu::App;

App::App(int &argc, char *argv[])
    : QApplication(argc, argv),
      exitAction(this),
      log(new AppLog()),
      logWindow(log),
      playerWindow(log) {

    // App configuratiom
    setOrganizationName("EvoMu");
    setApplicationName("EvoMu");

    // Quit application signal
    exitAction.setShortcuts(QKeySequence::Quit);
    connect(&exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    // Show log and player windows
    logWindow.show();
    playerWindow.show();
}
