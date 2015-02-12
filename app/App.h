#ifndef EVOMU_APP_APP_H
#define EVOMU_APP_APP_H

#include <memory>
#include <QApplication>
#include "AppLog.h"
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

            std::shared_ptr<AppLog> log;

            LogWindow logWindow;
            PlayerWindow playerWindow;
    };

}
}

#endif
