#include <RtMidi.h>
#include "Player.h"
#include "Song.h"
#include "Log.h"

using namespace EvoMu::Core;

/**
 * Initialise player
 */
Player::Player(std::shared_ptr<Log> log)
    : midi(new RtMidiOut()),
      log(log) {

    // Check available ports.
    unsigned int numPorts = midi->getPortCount();
    if (numPorts == 0) {
        log->message(LogStatus::Error, "No MIDI ports available");
    } else {
        // Open first available port.
        midi->openPort(0);
    }
}

/**
 * Stop player execution
 */
Player::~Player() {
    stop();
}

/**
 * Currently playing
 */
bool Player::isPlaying() {
    std::unique_lock<std::mutex> lock(mutex);
    return playing;
}

/**
 * A song / thread is playing but is paused
 */
bool Player::isPaused() {
    std::unique_lock<std::mutex> lock(mutex);
    return paused;
}

/**
 * Start playing specified song
 */
void Player::play(const std::string &str) {
    // Stop execution thread, if running
    stop();

    // Enable playing in execution thread
    paused = false;
    playing = true;

    // Initialise song
    song = std::unique_ptr<Song>(new Song(log, str));

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

            // Get the time offset in milliseconds
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(timeout - start);

            // Attempt to execute song
            if (song->execute(time.count(), message)) {
                // Send MIDI message
                midi->sendMessage(&message);
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
