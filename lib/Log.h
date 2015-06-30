#ifndef FMUSIC_CORE_LOG_H
#define FMUSIC_CORE_LOG_H

#include <string>

namespace fMusic {
namespace Core {

    enum class LogStatus { Error, Warning, Info, Debug };

    class Log {
        public:
            virtual ~Log() {}
            virtual void message(LogStatus status, const std::string &message) = 0;
    };

}
}

#endif
