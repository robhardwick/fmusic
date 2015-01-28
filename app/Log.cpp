#include "Log.h"

using namespace EvoMu::App;

void Log::message(EvoMu::Core::LogStatus status, const std::string &message) {
    emit write(status, message);
}
