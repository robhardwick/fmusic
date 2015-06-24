#ifndef EVOMU_APP_LOG_WINDOW_H
#define EVOMU_APP_LOG_WINDOW_H

#include <memory>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>
#include "Log.h"

namespace EvoMu {
namespace App {

    class LogWindow : public QMainWindow, public EvoMu::Core::Log {
        Q_OBJECT

        public:
            LogWindow();
            void message(EvoMu::Core::LogStatus status, const std::string &message);

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
