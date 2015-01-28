#ifndef EVOMU_APP_APP_H
#define EVOMU_APP_APP_H

#include <QApplication>
#include "Log.h"
#include "LogWindow.h"
#include "PlayerWindow.h"

namespace EvoMu {
namespace App {

    class App : public QApplication {
        Q_OBJECT

        public:
            App(int &argc, char *argv[]);

        private:
            QAction exitAction;

            Log log;
            Core::Player player;

            LogWindow logWindow;
            PlayerWindow playerWindow;
    };

}
}

#endif
