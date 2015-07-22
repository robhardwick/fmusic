#ifndef FMUSIC_APP_SETTINGS_WINDOW_H
#define FMUSIC_APP_SETTINGS_WINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

namespace fMusic {
namespace App {

    class SettingsWindow : public QMainWindow  {
        Q_OBJECT

        public:
            SettingsWindow();

        private slots:
            void updateInterval(const QString &text);
            void updateColour();

        protected:
            void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

        private:
            static const QSize DEFAULT_SIZE;
            static const QPoint DEFAULT_POS;

            QLineEdit intervalEdit;
            QFormLayout playerFormLayout;

            QPalette visualiserColourPalette;
            QPushButton visualiserColourBtn;
            QFormLayout visualiserFormLayout;
    };

}
}

#endif
