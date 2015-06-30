#ifndef FMUSIC_CORE_LUA_LOGGER_H
#define FMUSIC_CORE_LUA_LOGGER_H

struct lua_State;

namespace fMusic {
namespace Core {
namespace Lua {

    extern "C" {
        int Logger(lua_State *L);
    }

}
}
}

#endif
