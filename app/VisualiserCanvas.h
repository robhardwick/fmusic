#ifndef FMUSIC_APP_VISUALISER_CANVAS_H
#define FMUSIC_APP_VISUALISER_CANVAS_H

#include <memory>
#include <QOpenGLWidget>
#include <QPainter>
#include <QBrush>
#include "Log.h"

namespace fMusic {
namespace App {

    class VisualiserCanvas : public QOpenGLWidget  {
        Q_OBJECT

        public:
            VisualiserCanvas(std::shared_ptr<Core::Log> log, QWidget *parent = 0);
            ~VisualiserCanvas();

            void addBlock(QPoint block);

            static const QColor DEFAULT_COLOUR;

        protected:
            void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;

        private:
            static const int32_t BLOCK_WIDTH;
            static const int32_t BLOCK_HEIGHT;

            static const float BLOCKS_X;
            static const float BLOCKS_Y;

            std::shared_ptr<Core::Log> log;

            QPainter painter;
            QBrush backgroundBrush;

            QVector<QPoint> blocks;
    };

}
}

#endif
