#ifndef EVOMU_APP_PLAYER_WINDOW_H
#define EVOMU_APP_PLAYER_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>

#include "Log.h"
#include "Player.h"

namespace EvoMu {
namespace App {

    class PlayerWindow : public QMainWindow {
        Q_OBJECT

        public:
            PlayerWindow(Core::Player *player);

        protected:
            void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

        private slots:
            void newSong();
            void open();
            bool save();
            bool saveAs();
            void play();
            void stop();

        private:
            void setCurrentSong(const QString &fileName);
            void loadSong(const QString &fileName);
            bool saveSong(const QString &fileName);
            bool saveIfModified();

            QString curSong;

            QAction newAction;
            QAction openAction;
            QAction saveAction;
            QAction saveAsAction;
            QAction playAction;
            QAction stopAction;
            QAction closeAction;

            QMenu *fileMenu;
            QMenu *playMenu;
            QToolBar *toolbar;

            QPalette palette;
            QFont font;
            QPlainTextEdit textEdit;

            Core::Player *player;
    };

}
}

#endif
