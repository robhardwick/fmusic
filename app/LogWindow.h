#ifndef FMUSIC_APP_LOG_WINDOW_H
#define FMUSIC_APP_LOG_WINDOW_H

#include <memory>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>
#include "Log.h"

namespace fMusic {
namespace App {

    class LogWindow : public QMainWindow, public fMusic::Core::Log {
        Q_OBJECT

        public:
            LogWindow();
            void message(fMusic::Core::LogStatus status, const std::string &message);

        signals:
            void write(QString str);

        private slots:
            void append(QString str);
            void clear();

        private:
            QAction clearAction;
            QAction closeAction;

            QMenu *fileMenu;

            QPalette palette;
            QTextCharFormat format;
            QPlainTextEdit text;
    };

}
}

#endif
