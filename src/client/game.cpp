#include "game.h"
#include <scene/3d/node_3d.h>
#include <scene/3d/camera_3d.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <core/input/input_event.h>
#include <iostream>
#include <shared/entities/entity.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <shared/entities/mercenaries/test_mercenary.hpp>
#include <shared/data_holders/use_context.hpp>
#include <scene/main/viewport.h>
#include <core/config/engine.h>
#include <core/object/object.h>

#include <core/input/input_event.h>

#include <shared/entities/mercenaries/aal/aal.hpp>
#include <shared/registries.h>
#include <client/client.hpp>
#include <core/variant/dictionary.h>
#include <shared/helper_macros.h>

Game::Game() {
    
}

void Game::_init() {
    DISABLE_IN_EDITOR();
    //Allow node to process inputs
    set_process_unhandled_input(true);
    set_process(true);
}
/*
void Game::_on_entity_remote_spawn(Node *p_node)
{
    Entity *ent = Object::cast_to<Entity>(p_node);
    ERR_FAIL_COND_MSG(!ent, "Remote spawned node, which is not entity! Properties may be desynchronized!");

    Ref<SceneReplicationConfig> rep_cfg = mp_synchronizer->get_replication_config();
    List<StringName> networked_properties_names = ent->get_networked_properties();

    for(StringName property_name : networked_properties_names)
    {
        NodePath path = String(p_node->get_name()) + String(property_name);
        
        rep_cfg->add_property(path);
        rep_cfg->property_set_sync(path, false);
        rep_cfg->property_set_watch(path, true);
    }
}
*/
void Game::_tick()
{
    
}


void Game::_notification(int notification)
{
    DISABLE_IN_EDITOR();
    //Alternative implementation
    /*
    HashMap<int, Callable> map;
    if(map.has(notification)) {
        map.get(notification).call(this);
    }
    */

    switch (notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;
    case NOTIFICATION_READY:
        _ready();
        break;
    default:
        break;
    }
}

GameCamera *Game::setup_game_camera()
{
    game_camera = static_cast<GameCamera *>(get_node_or_null(NodePath("GameCamera")));
    if(!game_camera)
    {
        game_camera = memnew(GameCamera);
        game_camera->set_name("GameCamera");
        add_child(game_camera);
    }
    return game_camera;
}

void Game::_ready()
{
    DISABLE_IN_EDITOR();
    setup_game_camera();
    client = static_cast<Client *>(get_parent());
}

Vector3 Game::screenToWorld(const Vector2 &screenPos)
{
    
    //TODO: Project need to be used on camera node

    Vector3 rough_world_pos = game_camera->project_position(screenPos, 1000);
    Vector3 click_pos = game_camera->project_ray_origin(screenPos);

    double l = (rough_world_pos.x - click_pos.x);
    double m = (rough_world_pos.y - click_pos.y);
    double n = (rough_world_pos.z - click_pos.z);

    double world_x = click_pos.x - (click_pos.y/m)*l;
    double world_z = click_pos.z - (click_pos.y/m)*n;

    //y is zero because that doesn't matter
    return Vector3(world_x, 0, world_z);
}

void Game::unhandled_input(const Ref<InputEvent> &event)
{
    //Casting to InputEventMouseButton - If succeeds: It is valid type
    if(InputEventMouseButton *input_event_mouse_btn = Object::cast_to<InputEventMouseButton>(event.ptr()))
    {
        /*
        Entity *ent = client->get_player()->get_controlled_entity();
        if(!ent)
            return;
        */
        Vector2 screenPos = input_event_mouse_btn->get_position();
        Vector3 worldPos = screenToWorld(screenPos);

        /*
        UseContext use_context = {
            ent,
            ent->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };
        */

        //Convert screen to world cordinates
        printf("{ %f, %f, %f}\n", worldPos.x, worldPos.y, worldPos.z);

        if(input_event_mouse_btn->is_action_pressed("basic_attack"))
        {
            std::cout<<"ATTACK_ACTION"<<std::endl;

            //player->controlledEntity->use_basic_attack(use_context);

            Error err = rpc("attack_request", Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_mouse_btn->is_action_pressed("movement"))
        {
            std::cout<<"MOVEMENT_ACTION"<<std::endl;
            
            Error err = rpc("movement_request", Vector2(worldPos.x, worldPos.z));
            print_line("Client RPC Error", err);
        }
    }
    else if(const InputEventKey *input_event_key = Object::cast_to<InputEventKey>(event.ptr()))
    {
        Entity *ent = client->get_player()->get_controlled_entity();
        if(!ent)
            return;

        Vector3 worldPos = screenToWorld(get_viewport()->get_mouse_position());

        UseContext use_context = {
            ent,
            ent->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };

        //TODO: Ability use indicators
        if(input_event_key->is_action_pressed("cast_ability_1"))
        {
            printf("Q press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_FIRST, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_FIRST, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_2"))
        {
            printf("W press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_SECOND, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_SECOND, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_3"))
        {
            printf("E press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_THIRD, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_THIRD, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_4"))
        {
            printf("R press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_ULTIMATE, use_context);
            rpc("ability_use_request", AbilityCasterComponent::ABILITY_ULTIMATE, Vector2(worldPos.x, worldPos.z), 0);
        }
    }
}

void Game::_bind_methods()
{
    //Global signals
    //ADD_SIGNAL(MethodInfo("on_damage_taken", PropertyInfo(Variant::OBJECT, "entity"), PropertyInfo(Variant::OBJECT, "damage_object")));
}

Game::~Game()
{
    
}

//SH_Game definitions - Mostly empty on client-side
void Game::movement_request_impl(Vector2 target_pos) {

}

void Game::attack_request_impl(Vector2 target_pos, uint64_t target_entity_id) {

}

void Game::ability_use_request_impl(uint8_t ability_id, Vector2 target_pos, uint64_t target_entity_id) {

}