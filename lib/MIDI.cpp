#include <iostream>
#include <RtMidi.h>
#include "MIDI.h"
#include "Log.h"

using namespace EvoMu::Core::Instruments;

/**
 * Initialise MIDI Instrument
 */
MIDI::MIDI(std::shared_ptr<Log> log)
    : out(new RtMidiOut()),
      log(log) {

    // Check available ports.
    unsigned int numPorts = out->getPortCount();
    if (numPorts == 0) {
        log->message(LogStatus::Error, "No MIDI ports available");
    } else {
        // Open first available port.
        out->openPort(0);
    }
}

MIDI::~MIDI() = default;

/**
 * Send MIDI message
 */
void MIDI::message(Message &message) {
    out->sendMessage(&message);
}
