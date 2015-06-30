#include "App.h"

using namespace fMusic::App;

App::App(int &argc, char *argv[])
    : QApplication(argc, argv),
      exitAction(this),
      playerWindow() {

    // App configuratiom
    setOrganizationName("ƒMusic");
    setApplicationName("ƒMusic");

    // Quit application signal
    exitAction.setShortcuts(QKeySequence::Quit);
    connect(&exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    // Show player windows
    playerWindow.show();
}
