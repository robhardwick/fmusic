#ifndef FMUSIC_CORE_MIDI_INSTRUMENT_H
#define FMUSIC_CORE_MIDI_INSTRUMENT_H

#include <memory>
#include "Instrument.h"

class RtMidiOut;

namespace fMusic {
namespace Core {

    class Log;

    namespace Instruments {

        class MIDI: public Instrument {

            public:
                MIDI(std::shared_ptr<Log> log);
                ~MIDI();
                void message(Message &message);

            private:
                std::unique_ptr<RtMidiOut> out;
                std::shared_ptr<Log> log;
        };

    }

}
}

#endif
