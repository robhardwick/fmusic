#ifndef EVOMU_APP_LOG_WINDOW_H
#define EVOMU_APP_LOG_WINDOW_H

#include <memory>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>
#include "AppLog.h"

namespace EvoMu {
namespace App {

    class LogWindow : public QMainWindow {
        Q_OBJECT

        public:
            LogWindow(std::shared_ptr<AppLog> log);

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
