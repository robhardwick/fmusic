#ifndef FMUSIC_CORE_SONG_H
#define FMUSIC_CORE_SONG_H

#include <cstdint>
#include <memory>
#include <string>
#include "Message.h"

struct lua_State;

namespace fMusic {
namespace Core {

    class Log;

    class Song {
        public:
            Song(std::shared_ptr<Log> log, const std::string &str);
            bool execute(int32_t offset, Message &message);

        private:
            static const char *MESSAGE_VALUE_NAMES[];

            class LuaDeleter {
                public:
                    void operator()(lua_State *L);
            };

            std::shared_ptr<Log> log;
            std::unique_ptr<lua_State, LuaDeleter> L;

    };

}
}

#endif
