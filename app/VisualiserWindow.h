#ifndef FMUSIC_APP_VISUALISER_WINDOW_H
#define FMUSIC_APP_VISUALISER_WINDOW_H

#include <memory>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPainter>
#include <QBrush>
#include "Instrument.h"
#include "Log.h"

namespace fMusic {
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
            static const int BLOCK_WIDTH;
            static const int BLOCK_HEIGHT;
            static const float BLOCKS_X;
            static const float BLOCKS_Y;

            std::shared_ptr<Core::Log> log;

            QOpenGLWidget canvas;
            QPainter painter;

            QBrush backgroundBrush;
            QBrush blockBrush;

            QVector<QPoint> blocks;
    };

}
}

#endif
