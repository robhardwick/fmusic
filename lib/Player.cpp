#include <string>
#include "Player.h"

using namespace EvoMu::Core;

Player::Player(Log *log)
    : log(log) {

    // Check available ports.
    unsigned int numPorts = midi.getPortCount();
    if (numPorts == 0) {
        log->message(LogStatus::Error, "No MIDI ports available");
    } else {
        // Open first available port.
        midi.openPort(0);
    }

    // Initialise lua
    state = luaL_newstate();
    luaL_openlibs(state);
}

Player::~Player() {
    stop();
    lua_close(state);
}

/**
 * Start playing specified song
 */
void Player::play(const std::string &song) {
    // Stop execution thread, if running
    stop();

    // Set data for execution thread
    data.assign(song);
    playing = true;

    // Start execution thread
    thread = std::thread(&Player::task, this);
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
    }
}

/**
 * Schedule execution every X ms
 */
void Player::task() {
    // MIDI message buffer
    std::vector<unsigned char> message(3);

    // Playing/data mutex lock
    std::unique_lock<std::mutex> lock(mutex);

    // Current time as base timeout
    auto timeout = std::chrono::high_resolution_clock::now();

    do {
        // Set next execution time
        timeout += std::chrono::milliseconds(200);

        // Attempt to execute song
        if (execute(message)) {
            // Send MIDI message
            midi.sendMessage(&message);
        }

        // Sleep until next interval
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
    int numValues;

    if (luaL_dostring(state, data.c_str())) {
        // Log an error
        log->message(LogStatus::Error,
            std::string("Execution failed: ") + lua_tostring(state, -1));
        numValues = 1;
        goto cleanup;
    }

    // Check return values
    numValues = lua_gettop(state);
    if (numValues != 3) {
        log->message(LogStatus::Error,
            "Invalid message size (" + std::to_string(numValues) + ")");
        goto cleanup;
    }

    // Put return values into MIDI message
    for (int i = 0; i < 3; i++) {
        if (lua_isnumber(state, i)) {
            // Add to message
            message[i] = (unsigned char)lua_tointeger(state, i - 3);
        } else {
            // Log error and bail
            log->message(LogStatus::Error,
                std::string("Invalid ") + messageValueName[i] + " value");
            goto cleanup;
        }
    }

    // Log successful iteration
    log->message(LogStatus::Info,
        std::string("message sent [") +
        std::to_string((int)message[0]) + "," +
        std::to_string((int)message[1]) + "," +
        std::to_string((int)message[2]) + "]");

    // Success
    success = true;

    // Clean up stack
    cleanup:
        lua_pop(state, numValues);
        return success;
}
