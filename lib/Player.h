#ifndef EVOMU_CORE_PLAYER_H
#define EVOMU_CORE_PLAYER_H

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <RtMidi.h>
#include <lua.hpp>

namespace EvoMu {
namespace Core {

    enum class LogStatus { Error, Warning, Info, Debug };

    class Log {
        public:
            virtual ~Log() {}
            virtual void message(LogStatus status, const std::string &message) = 0;
    };

    class Player {

        public:
            Player(Log *log);
            ~Player();

            void play(const std::string &song);
            void stop();

        private:
            void task();
            bool execute(std::vector<unsigned char> &message);

            Log *log;
            std::string data;
            bool playing = false;

            std::thread thread;
            std::mutex mutex;

            RtMidiOut midi;
            lua_State *state;
    };

}
}

#endif
