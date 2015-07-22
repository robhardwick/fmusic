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

            static const QColor DEFAULT_COLOUR;

        public slots:
            void render();

        protected:
            void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

        private:
            static const QSize DEFAULT_SIZE;
            static const QPoint DEFAULT_POS;

            static const int32_t BLOCK_WIDTH;
            static const int32_t BLOCK_HEIGHT;

            static const float BLOCKS_X;
            static const float BLOCKS_Y;

            std::shared_ptr<Core::Log> log;

            QOpenGLWidget canvas;
            QPainter painter;

            QBrush backgroundBrush;

            QVector<QPoint> blocks;
    };

}
}

#endif
