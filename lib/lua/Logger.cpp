#include <lua.hpp>
#include "../Log.h"
#include "Logger.h"

using namespace fMusic::Core::Lua;

extern "C" {

int Logger(lua_State *L) {

    // Get log
    fMusic::Core::Log *log = (fMusic::Core::Log *)lua_touserdata(L, lua_upvalueindex(1));

    // Check number of arguments
    if (lua_gettop(L) != 1) {
        log->message(fMusic::Core::LogStatus::Error, "log(): Incorrect number of arguments");
        return 0;
    }

    // Get message string
    const char *msg = lua_tostring(L, 1);
    if (msg == NULL) {
        log->message(fMusic::Core::LogStatus::Error, "log(): Invalid argument");
        return 0;
    }

    // Send log message
    log->message(fMusic::Core::LogStatus::Info, msg);
    return 0;
}

}
