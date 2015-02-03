#ifndef EVOMU_APP_LOG_H
#define EVOMU_APP_LOG_H

#include <QObject>
#include <string>
#include "Player.h"

namespace EvoMu {
namespace App {

    class Log : public QObject, public EvoMu::Core::Log {
        Q_OBJECT

        public:
            void message(EvoMu::Core::LogStatus status, const std::string &message);

        signals:
            void write(QString str);

    };

}
}

#endif
