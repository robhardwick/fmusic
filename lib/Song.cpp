#include <stdexcept>
#include <lua.hpp>
#include "Song.h"
#include "Log.h"
#include "lua/Logger.h"
#include "lua/MIDI.h"

using namespace fMusic::Core;

/**
 * Constants
 */
const char *Song::MESSAGE_VALUE_NAMES[] = {"status", "data 1", "data 2"};

/**
 * Initialise lua and load song text
 */
Song::Song(std::shared_ptr<Log> log, const std::string &str)
    : log(log),
      L(luaL_newstate()) {

    // Load lua core libs
    luaL_openlibs(L.get());

    // Register logger
    lua_pushlightuserdata(L.get(), log.get());
    lua_pushcclosure(L.get(), Lua::Logger, 1);
    lua_setglobal(L.get(), "log");

    // Register MIDI file
    lua_pushlightuserdata(L.get(), log.get());
    lua_pushcclosure(L.get(), Lua::MIDI, 1);
    lua_setglobal(L.get(), "midi");

    // Load song
    if (luaL_loadstring(L.get(), str.c_str())) {
        log->message(LogStatus::Error,
            std::string("Parse failed: ") + lua_tostring(L.get(), -1));
        lua_pop(L.get(), 1);
        return;
    }

    lua_pcall(L.get(), 0, 0, 0);
}

/**
 * Cleanup lua instance
 */
void Song::LuaDeleter::operator()(lua_State *L) {
    lua_close(L);
}

/**
 * Execute the song
 */
bool Song::execute(int32_t offset, Message &message) {
    bool success = false;
    int numValues = 1;

    // Call function "f" with the time offset as the only argument
    lua_getfield(L.get(), LUA_GLOBALSINDEX, "f");
    lua_pushinteger(L.get(), offset);

    // Execute
    if (lua_pcall(L.get(), 1, 3, 0)) {
        // Log an error
        log->message(LogStatus::Error,
            std::string("Execution failed: ") + lua_tostring(L.get(), -1));
        goto cleanup;
    }

    // Check return values
    numValues = lua_gettop(L.get());
    if (numValues != 3) {
        log->message(LogStatus::Error,
            "Invalid message size (" + std::to_string(numValues) + ")");
        goto cleanup;
    }

    // Put return values into MIDI message
    for (int i = 0; i < 3; i++) {
        if (lua_isnumber(L.get(), i)) {
            // Add to message
            message[i] = (unsigned char)lua_tointeger(L.get(), i - 3);
        } else {
            // Log error and bail
            log->message(LogStatus::Error,
                std::string("Invalid ") + MESSAGE_VALUE_NAMES[i] + " value");
            goto cleanup;
        }
    }

    // Check message isn't empty
    if (message[0] != 0 && message[1] != 0 && message[2] != 0) {

        // Log message
        log->message(LogStatus::Info,
            std::string("message sent [") +
            std::to_string((int)message[0]) + "," +
            std::to_string((int)message[1]) + "," +
            std::to_string((int)message[2]) + "]");

        // Success
        success = true;

    }

    // Clean up stack
    cleanup:
        lua_pop(L.get(), numValues);
        return success;
}
