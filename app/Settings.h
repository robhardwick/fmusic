#ifndef FMUSIC_APP_SETTINGS_H
#define FMUSIC_APP_SETTINGS_H

#include <QSettings>

namespace fMusic {
namespace App {

    class Settings: public QSettings {
        Q_OBJECT

        public:
            Settings() : QSettings("fMusic", "fMusic") {};
    };

}
}

#endif
