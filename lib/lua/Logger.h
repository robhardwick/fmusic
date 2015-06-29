#ifndef EVOMU_CORE_LUA_LOGGER_H
#define EVOMU_CORE_LUA_LOGGER_H

struct lua_State;

namespace EvoMu {
namespace Core {
namespace Lua {

    extern "C" {
        int Logger(lua_State *L);
    }

}
}
}

#endif
