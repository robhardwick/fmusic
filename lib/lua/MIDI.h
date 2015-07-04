#ifndef FMUSIC_CORE_LUA_MIDI_H
#define FMUSIC_CORE_LUA_MIDI_H

struct lua_State;

namespace fMusic {
namespace Core {
namespace Lua {

    extern "C" {
        int MIDI(lua_State *L);
    }

}
}
}

#endif
