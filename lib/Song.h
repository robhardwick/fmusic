#ifndef EVOMU_CORE_SONG_H
#define EVOMU_CORE_SONG_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

struct lua_State;

namespace EvoMu {
namespace Core {

    class Log;

    class Song {

        public:
            Song(Log *log, const std::string &str);
            bool execute(int32_t offset, std::vector<unsigned char> &message);

        private:
            class LuaDeleter {
                public:
                    void operator()(lua_State *L);
            };

            Log *log;
            std::unique_ptr<lua_State, LuaDeleter> L;

    };

}
}

#endif
