#include "Player.h"

using namespace EvoMu::Core;

Player::Player(Log *log)
    : log(log),
      lua(NULL) {

    // Check available ports.
    unsigned int numPorts = midi.getPortCount();
    if (numPorts == 0) {
        log->message(LogStatus::Error, "No MIDI ports available");
    } else {
        // Open first available port.
        midi.openPort(0);
    }
}

Player::~Player() {
    stop();
}

bool Player::isPlaying() {
    std::unique_lock<std::mutex> lock(mutex);
    return playing;
}

bool Player::isPaused() {
    std::unique_lock<std::mutex> lock(mutex);
    return paused;
}

/**
 * Start playing specified song
 */
void Player::play(const std::string &song) {
    // Stop execution thread, if running
    stop();

    // Initialise lua
    lua = luaL_newstate();
    luaL_openlibs(lua);

    // Load song
    if (luaL_loadstring(lua, song.c_str())) {
        log->message(LogStatus::Error,
            std::string("Parse failed: ") + lua_tostring(lua, -1));
        lua_pop(lua, 1);
        return;
    }
    lua_pcall(lua, 0, 0, 0);

    // Enable playing in execution thread
    paused = false;
    playing = true;

    // Start execution thread
    thread = std::thread(&Player::task, this);
}

/**
 * Pause playing
 */
void Player::pause() {
    std::unique_lock<std::mutex> lock(mutex);
    paused = !paused;
}

/**
 * Stop playing
 */
void Player::stop() {
    // Check if execution thread is running
    if (thread.joinable()) {

        // Set playing flag to end thread
        std::unique_lock<std::mutex> lock(mutex);
        playing = false;
        lock.unlock();

        // Join thread until it returns
        thread.join();

        // Check if lua is initialised
        if (lua) {
            lua_close(lua);
        }
    }
}

/**
 * Schedule execution every X ms
 */
void Player::task() {
    // MIDI message buffer
    std::vector<unsigned char> message(3);

    // Playing mutex lock
    std::unique_lock<std::mutex> lock(mutex);

    // Current time as base timeout
    start = timeout = std::chrono::high_resolution_clock::now();

    do {
        // Only execute if paused is false
        if (!paused) {
            // Attempt to execute song
            if (execute(message)) {
                // Send MIDI message
                midi.sendMessage(&message);
            }
        }

        // Set next execution time
        timeout += std::chrono::milliseconds(10);

        // Sleep until next execution
        lock.unlock();
        std::this_thread::sleep_for(timeout - std::chrono::high_resolution_clock::now());
        lock.lock();

    // Continue execution while playing is true
    } while(playing);
}

/**
 * Execute the song
 */
const char *messageValueName[] = {"status", "data 1", "data 2"};

bool Player::execute(std::vector<unsigned char> &message) {
    bool success = false;
    int numValues = 1;

    // Call function "f"...
    lua_getfield(lua, LUA_GLOBALSINDEX, "f");

    // ...with the time offset in milliseconds as the only argument
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(timeout - start);
    lua_pushinteger(lua, time.count());

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
