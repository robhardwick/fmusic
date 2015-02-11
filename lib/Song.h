#ifndef EVOMU_CORE_SONG_H
#define EVOMU_CORE_SONG_H

#include <cstdint>
#include <string>
#include <vector>

struct lua_State;

namespace EvoMu {
namespace Core {

    class Log;

    class Song {

        public:
            Song(Log *log, const std::string &str);
            ~Song();
            bool execute(int32_t offset, std::vector<unsigned char> &message);

        private:
            Log *log;
            lua_State *lua;

    };

}
}

#endif
