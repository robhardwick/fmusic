#ifndef EVOMU_APP_VISUALISER_WINDOW_H
#define EVOMU_APP_VISUALISER_WINDOW_H

#include <memory>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QBrush>
#include "Instrument.h"
#include "Log.h"

namespace EvoMu {
namespace App {

    class VisualiserWindow : public QMainWindow, public Core::Instrument  {
        Q_OBJECT

        public:
            VisualiserWindow(std::shared_ptr<Core::Log> log);
            ~VisualiserWindow();

            void message(Core::Message &message);

        public slots:
            void render();

        private:
            std::shared_ptr<Core::Log> log;

            QOpenGLWidget canvas;

            QBrush backgroundBrush;
            QBrush blockBrush;

            struct Block {
                int x, y;
            };

            QVector<Block> blocks;
    };

}
}

#endif
