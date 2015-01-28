#include "App.h"

using namespace EvoMu::App;

App::App(int &argc, char *argv[])
    : QApplication(argc, argv),
      exitAction(this),
      player(&log),
      logWindow(&log),
      playerWindow(&player) {

    // App configuratiom
    setOrganizationName("EvoMu");
    setApplicationName("EvoMu");

    // Quit application signal
    exitAction.setShortcuts(QKeySequence::Quit);
    connect(&exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    // Show log window
    logWindow.show();

    // Show player window
    playerWindow.show();
}
