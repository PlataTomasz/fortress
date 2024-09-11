#include "game.h"
#include <server/server.h>
#include <shared/helper_macros.h>
#include <core/io/json.h>
#include <scene/scene_string_names.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <scene/resources/packed_scene.h>

#ifdef DEBUG_ARTSKR
#include <scene/3d/camera_3d.h>
#include <scene/main/viewport.h>
#include <shared/data_holders/action_context.hpp>
#endif

#include <shared/string_names/component_stringnames.h>
#include <shared/gamemodes/gamemode.h>
#include <scene/main/timer.h>
#include <shared/entities/components/movement/movement_component.h>

Game::Game()
{
    //Temporary
    gameinfo["level"] = "Aram";
}

void Game::_on_game_over() {
    // TODO: What if somehow it happened?
    ERR_FAIL_NULL_MSG(server, "Server couldn't be terminated! 'server' is NULL!"); // That should NEVER happen
    Ref<SceneTreeTimer> timer = SceneTree::get_singleton()->create_timer(5);

    timer->connect("timeout", callable_mp(static_cast<Realm *>(server), &Server::close));
}

void Game::_on_gamemode_change(Gamemode *new_gamemode) {
    if(current_gamemode) {
        current_gamemode->disconnect("game_over", callable_mp(this, &Game::_on_game_over));
    }

    ERR_FAIL_NULL(new_gamemode);
    new_gamemode->connect("game_over", callable_mp(this, &Game::_on_game_over));
}

void Game::_post_level_load() {
    ERR_FAIL_NULL(game_level);
    _on_gamemode_change(game_level->get_gamemode());
}

void Game::_init() {
    connect("post_level_load", callable_mp(this, &Game::_post_level_load));
}
 
void Game::_ready()
{
    DISABLE_IN_EDITOR();
    //No error checking!
    load_game_level(String(gameinfo["level"]));
    setup_game();

    server = static_cast<Server *>(get_parent());
}

//Notifications are called cascade
void Game::_notification(int notification) {
	DISABLE_IN_EDITOR();
	switch (notification) {
		case NOTIFICATION_READY: {
			_ready();
		} break;

		case NOTIFICATION_POSTINITIALIZE: {
			_init();
		} break;

		default:
			break;
	}
}

void Game::_bind_methods()
{
    ADD_SIGNAL(MethodInfo("gamemode_change", PropertyInfo(Variant::OBJECT, "new_gamemode")));
}

// Player send invalid playerdata or didn't send it at all - kick him
void Game::_on_playerdata_fail(int peer_id) {
    // Cleanup disconnect timer - no longer needed
    if (playerdata_timers.has(peer_id)) {
        Ref<SceneTreeTimer> timer = playerdata_timers.get(peer_id);
    }

    print_line("Peer ", peer_id, " disconnected. Reason: Invalid playerdata");
    server->disconnect_peer(peer_id, "Invalid playerdata!");
}

// Expected to arrive shortly after player connects
void Game::_on_receive_playerdata(Dictionary playerdata) {
    int peer_id = get_multiplayer()->get_remote_sender_id();
    Ref<Player> ply = server->get_player(peer_id);
}

void Game::attack_request_impl(Vector2 target_pos, uint64_t target_entity_id) {
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Attack request received from", peer_id);
    Server *sv = Object::cast_to<Server>(get_parent());
    ERR_FAIL_NULL(sv);
    Ref<Player> ply = sv->get_player(peer_id);
    ERR_FAIL_COND(ply.is_null());
    Mercenary *mercenary = ply->get_controlled_entity();
    ERR_FAIL_NULL(mercenary);
    AbilityCasterComponent *ability_caster_component = mercenary->get_ability_caster_component();
    ERR_FAIL_NULL(ability_caster_component);
    Ref<ActionContext> ctx = memnew(ActionContext(mercenary, mercenary->get_position(), Vector3(target_pos.x, 0, target_pos.y), nullptr));
    ability_caster_component->use_basic_attack(ctx);
}

void Game::ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id) {
    int peer_id = get_multiplayer()->get_remote_sender_id();
    print_line("Ability use request received from", peer_id);
    // Get Player that used an ability
    // FIXME: Will break if game is not direct child of server
    Server *sv = Object::cast_to<Server>(get_parent());
    ERR_FAIL_NULL(sv);
    Ref<Player> ply = sv->get_player(peer_id);
    ERR_FAIL_COND(ply.is_null());
    Mercenary *mercenary = ply->get_controlled_entity();
    ERR_FAIL_NULL(mercenary);
    AbilityCasterComponent *ability_caster_component = mercenary->get_ability_caster_component();
    ERR_FAIL_NULL(ability_caster_component);
    Ref<ActionContext> ctx = memnew(ActionContext(mercenary, mercenary->get_position(), Vector3(target_pos.x, 0, target_pos.y), nullptr));
    ability_caster_component->use_ability(ability_id, ctx);
}

void Game::movement_request_impl(Vector2 target_pos)
{
    int peer_id = get_multiplayer()->get_remote_sender_id();

    print_line("Movement request to", target_pos, "from peer", peer_id);
    
    Ref<Player> player = server->get_player(peer_id);
    ERR_FAIL_COND_MSG(player.is_null(), "Sender peer has no corresponding player");

    Entity *issuer = player->get_controlled_entity();
    ERR_FAIL_COND_MSG(!issuer, "Player doesn't control any entity!");

    MovementComponent *movement_component = static_cast<MovementComponent *>(issuer->get_node_or_null(NodePath("MovementComponent")));
    ERR_FAIL_NULL(movement_component);
    movement_component->set_destination_position(Vector3(target_pos.x,0,target_pos.y));

    //TODO: Parse movement request here

    //FIXME: Connection is established, RPC work, Replication doesn't
    //Entity *ent = static_cast<Entity *>(get_node(NodePath("Level/Entities/Entity")));

    //ent->set_position(ent->get_position() + Vector3(1,0,0));
}