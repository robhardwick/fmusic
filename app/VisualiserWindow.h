#ifndef FMUSIC_APP_VISUALISER_WINDOW_H
#define FMUSIC_APP_VISUALISER_WINDOW_H

#include <memory>
#include <QMainWindow>
#include "VisualiserCanvas.h"
#include "Instrument.h"
#include "Log.h"

namespace fMusic {
namespace App {

    class VisualiserWindow : public QMainWindow, public Core::Instrument  {
        Q_OBJECT

        public:
            VisualiserWindow(std::shared_ptr<Core::Log> log);
            ~VisualiserWindow();

            void message(Core::Message &message) override;

        public slots:
            void render();

        protected:
            void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

        private:
            static const QSize DEFAULT_SIZE;
            static const QPoint DEFAULT_POS;

            std::shared_ptr<Core::Log> log;

            VisualiserCanvas canvas;
    };

}
}

#endif
