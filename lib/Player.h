#ifndef EVOMU_CORE_PLAYER_H
#define EVOMU_CORE_PLAYER_H

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

class RtMidiOut;

namespace EvoMu {
namespace Core {

    class Log;
    class Song;

    class Player {

        public:
            Player(Log *log);
            ~Player();

            bool isPlaying();
            bool isPaused();

            void play(const std::string &song);
            void pause();
            void stop();

        private:
            void task();
            bool execute(std::vector<unsigned char> &message);

            RtMidiOut *midi;

            Log *log;
            Song *song;

            bool playing = false;
            bool paused = false;
            std::chrono::high_resolution_clock::time_point start, timeout;

            std::thread thread;
            std::mutex mutex;
    };

}
}

#endif
