#include <fstream>
#include <iostream>
#include <sstream>
#include <lua.hpp>
#include "../Log.h"
#include "MIDI.h"
#include "MIDIFile.h"

using namespace fMusic::Core::Lua;

extern "C" {

/**
 * Read a MIDI file
 */
int MIDI(lua_State *L) {

    // Get log
    fMusic::Core::Log *log = (fMusic::Core::Log *)lua_touserdata(L, lua_upvalueindex(1));

    // Check number of arguments
    if (lua_gettop(L) != 1) {
        log->message(fMusic::Core::LogStatus::Error, "midi(): Incorrect number of arguments");
        return 0;
    }

    // Get MIDI filename argument
    const char *filename = lua_tostring(L, 1);
    if (filename == NULL) {
        log->message(fMusic::Core::LogStatus::Error, "midi(): Invalid argument");
        return 0;
    }

    // Open file
    log->message(fMusic::Core::LogStatus::Info, std::string("Opening file \"") + filename + "\"...");
    MIDIFile file(filename);

    // Log number of events
    log->message(fMusic::Core::LogStatus::Info, std::string("Got ") + std::to_string(file.events.size()) + " events");

    // Create new table on Lua stack to hold events
    lua_newtable(L);

    // Iterate over events
    int idx = 0;
    for (auto &event: file.events) {

        // Create table to hold event
        lua_newtable(L);

        // Add status byte
        lua_pushnumber(L, event.status);
        lua_rawseti(L, -2, 1);

        // Add data1 byte
        lua_pushnumber(L, event.data1);
        lua_rawseti(L, -2, 2);

        // Add data2 byte
        lua_pushnumber(L, event.data2);
        lua_rawseti(L, -2, 3);

        // Add time delta
        lua_pushnumber(L, event.delta);
        lua_rawseti(L, -2, 4);

        // Close table
        lua_rawseti(L, -2, ++idx);

    }

    return 1;

}

}


