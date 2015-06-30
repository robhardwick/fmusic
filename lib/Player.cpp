#include <chrono>
#include "Player.h"
#include "Song.h"
#include "Log.h"
#include "Instrument.h"

using namespace fMusic::Core;

/**
 * Initialise player
 */
Player::Player(std::shared_ptr<Log> log)
    : log(log) {}

/**
 * Stop player execution
 */
Player::~Player() {
    stop();
}

/**
 * Add instrument
 */
void Player::addInstrument(std::shared_ptr<Instrument> instrument) {
    instruments.push_back(instrument);
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
    std::chrono::high_resolution_clock::time_point start, timeout;
    start = timeout = std::chrono::high_resolution_clock::now();

    do {
        // Only execute if paused is false
        if (!paused) {

            // Get the time offset in milliseconds
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(timeout - start);

            // Attempt to execute song
            if (song->execute(time.count(), message)) {

                // Iterate over instruments, sending the message to each
                for (auto instrument : instruments) {
                    instrument->message(message);
                }

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
