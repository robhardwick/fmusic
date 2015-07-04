#ifndef FMUSIC_CORE_LUA_MIDIFILE_H
#define FMUSIC_CORE_LUA_MIDIFILE_H

#include <fstream>
#include <vector>

namespace fMusic {
namespace Core {
namespace Lua {

    struct MIDIEvent {
        uint32_t delta;
        uint8_t status, data1, data2;
    };

    class MIDIFile {
        public:
            MIDIFile(std::string filename);

            std::vector<MIDIEvent> events;

        private:
            static const char *CHUNK_HEADER;
            static const char *CHUNK_TRACK;

            bool readChunk();
            void readHeader(size_t length);
            void readTrack(size_t length);

            template<size_t n, class T> inline T read();
            template<class T> inline T readVar();

            std::ifstream file;

            uint16_t format;
            uint16_t numTracks;
            int16_t division;
    };

}
}
}

#endif
