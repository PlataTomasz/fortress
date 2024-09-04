#include "gamemode.h"

void Gamemode::server_rpc_player_lost_game() {
    emit_signal("player_lost_game");
}