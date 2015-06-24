#ifndef EVOMU_CORE_INSTRUMENT_H
#define EVOMU_CORE_INSTRUMENT_H

#include "Message.h"

namespace EvoMu {
namespace Core {

    class Instrument {

        public:
            virtual ~Instrument() {}
            virtual void message(Message &message) = 0;
    };

}
}

#endif
