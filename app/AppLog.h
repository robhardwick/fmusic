#ifndef EVOMU_APP_APPLOG_H
#define EVOMU_APP_APPLOG_H

#include <QObject>
#include <string>
#include "Log.h"

namespace EvoMu {
namespace App {

    class AppLog : public QObject, public EvoMu::Core::Log {
        Q_OBJECT

        public:
            void message(EvoMu::Core::LogStatus status, const std::string &message);

        signals:
            void write(QString str);

    };

}
}

#endif
