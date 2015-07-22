#ifndef FMUSIC_CORE_PLAYER_H
#define FMUSIC_CORE_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include "Message.h"

namespace fMusic {
namespace Core {

    class Log;
    class Instrument;
    class Song;

    class Player {

        public:
            Player(std::shared_ptr<Log> log);
            ~Player();

            bool isPlaying();
            bool isPaused();

            void addInstrument(std::shared_ptr<Instrument> instrument);
            void setInterval(int32_t value);

            void play(const std::string &song);
            void pause();
            void stop();

            static const int32_t DEFAULT_INTERVAL = 10;

        private:
            void task();
            bool execute(Message &message);

            std::shared_ptr<Log> log;
            std::vector< std::shared_ptr<Instrument> > instruments;
            std::unique_ptr<Song> song;

            bool playing = false;
            bool paused = false;

            int32_t interval;

            std::thread thread;
            std::mutex mutex;
    };

}
}

#endif
