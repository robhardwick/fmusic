#ifndef EVOMU_APP_PLAYER_WINDOW_H
#define EVOMU_APP_PLAYER_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>
#include "LogWindow.h"
#include "VisualiserWindow.h"
#include "SyntaxHighlight.h"
#include "Player.h"
#include "MIDI.h"

namespace EvoMu {
namespace App {

    class PlayerWindow : public QMainWindow {
        Q_OBJECT

        public:
            PlayerWindow(std::shared_ptr<LogWindow> log, std::shared_ptr<VisualiserWindow> visualiser);

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
            void setPlayAction();
            void setCurrentSong(const QString &fileName);
            void loadSong(const QString &fileName);
            bool saveSong(const QString &fileName);
            bool saveIfModified();

            Core::Player player;
            std::shared_ptr<Core::Instruments::MIDI> midi;

            QString curSong;

            QIcon playIcon;
            QIcon pauseIcon;

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

            QFont font;
            QPlainTextEdit textEdit;

            SyntaxHighlight highlighter;
    };

}
}

#endif
