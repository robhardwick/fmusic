#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include "Log.h"
#include "Player.h"
#include "MIDI.h"

using namespace fMusic::Core;

sig_atomic_t playing;

/**
 * Log to stdout
 */
class LogCLI : public Log {
    public:
        LogCLI() {};
        void message(LogStatus status, const std::string &message) {
            std::cout << "[fmu] " << message << "\n";
        }
};

/**
 * Handle SIGINT
 */
void sigIntHandler(int s) {
    playing = false;
}

/**
 * Run
 */
int main(int argc, char *argv[]) {

    // Create log
    auto log = std::make_shared<LogCLI>();

    // Ensure a song argument was given
    if (argc != 2) {
        log->message(LogStatus::Error, std::string("Usage: ") + argv[0] + " song.fmu");
        return 1;
    }

    // Create player
    Player player(log);

    // Create MIDI output
    auto midi = std::make_shared<Instruments::MIDI>(log);
    player.addInstrument(midi);

    // Open song file
    std::ostringstream buf;
    std::ifstream input(argv[1]);

    // Check file opened succesfully
    if (!input.is_open()) {
        log->message(LogStatus::Error, std::string("Unable to open ") + argv[1]);
        return 1;
    }

    // Read song file contents
    buf << input.rdbuf();

    // Handle SIGINT
    struct sigaction handler;
    handler.sa_handler = sigIntHandler;
    sigemptyset(&handler.sa_mask);
    handler.sa_flags = 0;
    sigaction(SIGINT, &handler, NULL);

    // Play song
    log->message(LogStatus::Info, std::string("Playing ") + argv[1]);
    playing = true;
    player.play(buf.str());

    // Loop unit SIGINT
    while(playing);

    log->message(LogStatus::Info, "Exiting...");
    return 0;

}
