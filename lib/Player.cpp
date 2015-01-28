#include "Player.h"

using namespace EvoMu::Core;

Player::Player(Log *log)
    : log(log) {
    log->message(LogStatus::Info, "Initializing luajit...");
    state = luaL_newstate();
	luaL_openlibs(state);
}

Player::~Player() {
    lua_close(state);
    log->message(LogStatus::Info, "Closed luajit");
}

void Player::play(const std::string &song) {
    if (luaL_dostring(state, song.c_str())) {
        log->message(LogStatus::Error, lua_tostring(state, -1));
        lua_pop(state, 1);
    }
}

void Player::stop() {
    // TODO
}
