#ifndef FMUSIC_CORE_INSTRUMENT_H
#define FMUSIC_CORE_INSTRUMENT_H

#include "Message.h"

namespace fMusic {
namespace Core {

    class Instrument {

        public:
            virtual ~Instrument() {}
            virtual void message(Message &message) = 0;
    };

}
}

#endif
