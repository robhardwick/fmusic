#include <stdexcept>
#include <iostream>
#include "MIDIFile.h"

using namespace fMusic::Core::Lua;

/**
 * Constants
 */
const char *MIDIFile::CHUNK_HEADER = "MThd";
const char *MIDIFile::CHUNK_TRACK = "MTrk";

/**
 * Open and read MIDI file
 */
MIDIFile::MIDIFile(std::string filename)
    : file(filename, std::ios::binary) {

    // Ensure open was successful
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open");
    }

    // Read chunks until EOF
    while(readChunk());

}

/**
 * Read a MIDI file chunk
 */
bool MIDIFile::readChunk() {

    // Get chunk ID
    char id[4];
    file.read((char *)&id, sizeof(id));

    // Get chunk length
    auto length = read<4, size_t>();

    // Header chunk
    if (memcmp(id, CHUNK_HEADER, sizeof(id)) == 0) {
        readHeader(length);

    // Track chunk
    } else if (memcmp(id, CHUNK_TRACK, sizeof(id)) == 0) {
        readTrack(length);

    // Unknown (ignore)
    } else {
        file.ignore(length);
    }

    return !(file.eof());

}

/**
 * Read header chunk
 */
void MIDIFile::readHeader(size_t length) {

    // Get file format
    format = read<2, uint16_t>();

    // Get number of tracks
    numTracks = read<2, uint16_t>();

    // Get division
    division = read<2, int16_t>();

    // Skip any other data
    file.ignore(length - 6);

}

/**
 * Read track chunk
 */
void MIDIFile::readTrack(size_t length) {

    std::streampos end = length + file.tellg();
    while(file.tellg() < end) {

        auto delta = readVar<uint32_t>();
        auto status = read<1, uint8_t>();

        // Ignore sysex events
        if (status == 0xF0 || status == 0xF7) {
            file.ignore(readVar<size_t>());

        // Ignore meta events
        } else if (status == 0xFF) {
            file.ignore(1);
            file.ignore(readVar<size_t>());

        // Handle MIDI event
        } else {
            events.push_back({
                .delta = delta,
                .status = status,
                .data1 = read<1, uint8_t>(),
                .data2 = read<1, uint8_t>()
            });
        }

    }

}

/**
 * Read n byte value from file
 */
template<size_t n, class T>
inline T MIDIFile::read() {
    char buf[n];
    file.read((char *)&buf, n);
    T value = *buf;
    if (n >= 2) {
        value = (buf[0] & 0xff);
        value = (value<<8) + (buf[1] & 0xff);
    }
    if (n >= 4) {
        value = (value<<8) + (buf[2] & 0xff);
        value = (value<<8) + (buf[3] & 0xff);
    }
    return value;
}

/**
 * Read variable length value from file
 */
template<class T>
inline T MIDIFile::readVar() {
	int c = file.get();
	uint32_t value = c;
    if (c & 0x80) {
        value &= 0x7f;
        do {
            c = file.get();
            value = (value << 7) + (c & 0x7f);
        } while (c & 0x80);
    }
    return value;
}
