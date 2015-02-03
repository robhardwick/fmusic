#include <sstream>
#include <QDateTime>
#include "Log.h"

using namespace EvoMu::App;

const char *logStatusName[] = {"error", "warn", "info", "debug"};

/**
 * Format log message and send "write" signal
 */
void Log::message(EvoMu::Core::LogStatus status, const std::string &message) {
    // Get current date and time
    QDateTime dateTime(QDateTime::currentDateTime());
    std::string dateTimeStr = dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz").toStdString();

    // Format as "[<timestamp>][<status>] message"
    std::ostringstream out;
    out << '[' << dateTimeStr << "][" << logStatusName[(int)status] << "] " << message;

    emit write(QString(out.str().c_str()));
}
