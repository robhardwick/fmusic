#ifndef EVOMU_CORE_PLAYER_H
#define EVOMU_CORE_PLAYER_H

#include <string>
#include <vector>
#include <memory>
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
            Player(std::shared_ptr<Log> log);
            ~Player();

            bool isPlaying();
            bool isPaused();

            void play(const std::string &song);
            void pause();
            void stop();

        private:
            void task();
            bool execute(std::vector<unsigned char> &message);

            std::unique_ptr<RtMidiOut> midi;

            std::shared_ptr<Log> log;
            std::unique_ptr<Song> song;

            bool playing = false;
            bool paused = false;
            std::chrono::high_resolution_clock::time_point start, timeout;

            std::thread thread;
            std::mutex mutex;
    };

}
}

#endif
