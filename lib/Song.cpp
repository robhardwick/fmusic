#include <stdexcept>
#include <lua.hpp>
#include "Song.h"
#include "Log.h"

using namespace EvoMu::Core;

/**
 * Initialise lua and load song text
 */
Song::Song(Log *log, const std::string &str)
    : log(log),
      lua(luaL_newstate()) {

    // Load lua core libs
    luaL_openlibs(lua);

    // Load song
    if (luaL_loadstring(lua, str.c_str())) {
        log->message(LogStatus::Error,
            std::string("Parse failed: ") + lua_tostring(lua, -1));
        lua_pop(lua, 1);
        throw std::runtime_error("FAILED");
    }
    lua_pcall(lua, 0, 0, 0);
}

/**
 * Cleanup
 */
Song::~Song() {
    lua_close(lua);
}

/**
 * Execute the song
 */
const char *messageValueName[] = {"status", "data 1", "data 2"};

bool Song::execute(int32_t offset, std::vector<unsigned char> &message) {
    bool success = false;
    int numValues = 1;

    // Call function "f" with the time offset as the only argument
    lua_getfield(lua, LUA_GLOBALSINDEX, "f");
    lua_pushinteger(lua, offset);

    // Execute
    if (lua_pcall(lua, 1, 3, 0)) {
        // Log an error
        log->message(LogStatus::Error,
            std::string("Execution failed: ") + lua_tostring(lua, -1));
        goto cleanup;
    }

    // Check return values
    numValues = lua_gettop(lua);
    if (numValues != 3) {
        log->message(LogStatus::Error,
            "Invalid message size (" + std::to_string(numValues) + ")");
        goto cleanup;
    }

    // Put return values into MIDI message
    for (int i = 0; i < 3; i++) {
        if (lua_isnumber(lua, i)) {
            // Add to message
            message[i] = (unsigned char)lua_tointeger(lua, i - 3);
        } else {
            // Log error and bail
            log->message(LogStatus::Error,
                std::string("Invalid ") + messageValueName[i] + " value");
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
        lua_pop(lua, numValues);
        return success;
}
