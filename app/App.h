#ifndef FMUSIC_APP_APP_H
#define FMUSIC_APP_APP_H

#include <memory>
#include <QApplication>
#include "PlayerWindow.h"

namespace fMusic {
namespace App {

    class App : public QApplication {
        Q_OBJECT

        public:
            App(int &argc, char *argv[]);

        private:
            QAction exitAction;
            PlayerWindow playerWindow;
    };

}
}

#endif
