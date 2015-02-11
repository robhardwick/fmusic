#ifndef EVOMU_CORE_LOG_H
#define EVOMU_CORE_LOG_H

namespace EvoMu {
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
