#include "game.hpp"
#include <scene/3d/node_3d.h>
#include <scene/3d/camera_3d.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>
#include <core/input/input_event.h>
#include <iostream>
#include "entities/entity.hpp"
#include "entities/mercenaries/mercenary.hpp"
#include <client/entities/mercenaries/test_mercenary.hpp>
#include "game_logic/abilities/use_context.hpp"
#include <scene/main/viewport.h>
#include <core/config/engine.h>
#include <client/status_effects/status_effect_manager.hpp>
#include <core/object/object.h>
#include <client/string_names/game_string_names.h>

#include <core/input/input_event.h>

#include "entities/mercenaries/tundra/tundra.hpp"
#include <client/entities/mercenaries/fist_mercenary/fist_mercenary.hpp>
#include <client/entities/mercenaries/aal/aal.hpp>
#include <shared/registries.h>
#include <client/game_logic/abilities/test_ability.hpp>
#include <client/game_logic/abilities/test_ability2.hpp>
#include <client/networking/requests/c_game_requests.h>
#include <client/networking/c_sync_events.h>
#include <client/client.hpp>
#include <core/variant/dictionary.h>
#include <shared/helper_macros.h>

Game::Game()
{
    DISABLE_IN_EDITOR();
    //Allow node to process inputs
    set_process_unhandled_input(true);
    set_process(true);

    connect(SceneStringNames::get_singleton()->ready, callable_mp(this, &Game::_ready));
    connect(SceneStringNames::get_singleton()->_process, callable_mp(this, &Game::_process));

    //RPC config
    ADD_RPC_CONFIG(movement_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(attack_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(ability_use_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);
    ADD_RPC_CONFIG(player_cfg_update_request, MultiplayerAPI::RPC_MODE_ANY_PEER, MultiplayerPeer::TRANSFER_MODE_RELIABLE, 0, false);

    initialize_registries();
}

void Game::setup_game()
{
    entity_synchronizer = memnew(MultiplayerSynchronizer);
    entity_spawner = memnew(MultiplayerSpawner);

    add_child(entity_spawner);
    add_child(entity_synchronizer);

    NodePath entities_nodepath = NodePath("../Level/Entities");

    entity_spawner->set_spawn_path(entities_nodepath);
    entity_spawner->add_spawnable_scene("res://entities/Entity.tscn");

    entity_synchronizer->set_root_path(entities_nodepath);

    if(entity_synchronizer->get_replication_config().is_null())
        entity_synchronizer->set_replication_config(memnew(SceneReplicationConfig));

    entity_spawner->connect("spawned", callable_mp(this, Game::_on_entity_remote_spawn));
}

void Game::_on_entity_remote_spawn(Node *p_node)
{
    Entity *ent = Object::cast_to<Entity>(p_node);
    ERR_FAIL_COND_MSG(!ent, "Remote spawned node, which is not entity! Properties may be desynchronized!");

    Ref<SceneReplicationConfig> rep_cfg = entity_synchronizer->get_replication_config();
    List<StringName> networked_properties_names = ent->get_networked_properties();

    for(StringName property_name : networked_properties_names)
    {
        NodePath path = String(p_node->get_name()) + String(property_name);
        
        rep_cfg->add_property(path);
        rep_cfg->property_set_sync(path, false);
        rep_cfg->property_set_watch(path, true);
    }
}

void Game::_process()
{
    
}

/*
void Game::_notification(int notification)
{
    switch (notification)
    {
    case NOTIFICATION_PROCESS:
        {
            //Dispatch GameCommands
            for(C_SyncEvent *sync_event : sync_events)
            {
                sync_event->execute(this);
            }
        }
        break;
    
    case NOTIFICATION_ENTER_TREE:
    {
        client = static_cast<Client *>(get_parent());
    }
    break;

    default:
        break;
    }
}
*/

void Game::_ready()
{
    setup_game();
    
    GameMap *tmp_mapInstance = (GameMap*)get_node(NodePath("Map"));
    if(tmp_mapInstance)
    {
        this->gameMap = tmp_mapInstance;
        std::cout<<"Map detected!"<<std::endl;
    }
    else
    {
        //TODO: Load map from file - currently left in undefined state
        std::cout<<"Map was not loaded!"<<std::endl;
    }

    GameCamera *tmp_camera = (GameCamera*)get_node(NodePath("Camera"));
    if(tmp_camera)
    {
        this->camera = tmp_camera;
        std::cout<<"Game Camera detected!"<<std::endl;
    }
    else
    {
        GameCamera *game_camera = memnew(GameCamera);
        add_child(game_camera);

        this->camera = game_camera;
        std::cout<<"Camera was not loaded! Creating one instead."<<std::endl;
    }  

    printf("Initializing StatusEffectManager...");
    StatusEffectManager::get_singleton();
    printf("Done!");

    //Tundra *ent = memnew(Tundra);

    //Note: get_item() might return NULL
    //TODO: Handle NULL case
    Mercenary* ent = Registries::get_singleton()->MERCENARIES.get_item(GameStringNames::get_singleton()->SWORD_MERCENARY);

    ent->set_name("ControlledEntity");
    this->add_child(ent);
    ent->set_position(Vector3( 2, 2, 2));
    
    Vector3 redSpawnPoint = Vector3();
    Node3D *redSpawnNode = nullptr;
    //(Node3D*)get_node(NodePath("Map/SpawnRed"));

    if(!redSpawnNode)
    {
        printf("No spawn node defined! Defaulting to map center (0, 0)");
    }
    else
    {
        redSpawnPoint = redSpawnNode->get_position();
    }

    player = new Player();
    player->controlledEntity = ent;
    player->controlledEntity->set_position(redSpawnPoint);

    camera->startFollowingNode(ent);

    get_multiplayer()->connect("connected_to_server", callable_mp(this, &Game::_on_connect_to_remote_game));
    //Workaround for a bug in raw version - We connect to server BEFORE the signal is connected!
    if(get_multiplayer()->get_multiplayer_peer()->get_connection_status() == MultiplayerPeer::ConnectionStatus::CONNECTION_CONNECTED)
    {
        _on_connect_to_remote_game();
    }
    
}

void Game::initialize_registries()
{
    //Mercenaries
    Ability *SWORD_MERCENARY_ABILITIES[Mercenary::ABILITY_MAX] = {new TestAbility2(), new TestAbility(), new TestAbility2(), new TestAbility2(), new TestAbility2()};
    Registries::get_singleton()->MERCENARIES.register_item(GameStringNames::get_singleton()->SWORD_MERCENARY, memnew(Mercenary(SWORD_MERCENARY_ABILITIES)));

    //Basic attack providers


    //Abilities
    /*
    Registries::ABILITIES.register_item(GameStringNames::get_singleton()->SWORD_MERCENARY_PASSIVE_ABILITY, new SwordMercenaryPassiveAbility());
    Registries::ABILITIES.register_item(GameStringNames::get_singleton()->SWORD_MERCENARY_ACTIVE_ABILITY_1, new SwordMercenaryActiveAbility1());
    Registries::ABILITIES.register_item(GameStringNames::get_singleton()->SWORD_MERCENARY_ACTIVE_ABILITY_2, new SwordMercenaryActiveAbility2());
    Registries::ABILITIES.register_item(GameStringNames::get_singleton()->SWORD_MERCENARY_ACTIVE_ABILITY_3, new SwordMercenaryActiveAbility3());
    Registries::ABILITIES.register_item(GameStringNames::get_singleton()->SWORD_MERCENARY_ACTIVE_ABILITY_4, new SwordMercenaryActiveAbility4());
    */
}

Vector3 Game::screenToWorld(const Vector2 &screenPos)
{
    
    //TODO: Project need to be used on camera node

    Vector3 roughWorldPos = camera->project_position(screenPos, 1000);
    Vector3 clickPos = camera->project_ray_origin(screenPos);

    double l = (roughWorldPos.x - clickPos.x);
    double m = (roughWorldPos.y - clickPos.y);
    double n = (roughWorldPos.z - clickPos.z);

    double world_x = clickPos.x - (clickPos.y/m)*l;
    double world_z = clickPos.z - (clickPos.y/m)*n;

    //y is zero because that doesn't matter
    return Vector3(world_x, 0, world_z);
}

void Game::unhandled_input(const Ref<InputEvent> &event)
{
    //Casting to InputEventMouseButton - If succeeds: It is valid type
    if(InputEventMouseButton *input_event_mouse_btn = Object::cast_to<InputEventMouseButton>(event.ptr()))
    {
        Vector2 screenPos = input_event_mouse_btn->get_position();
        Vector3 worldPos = screenToWorld(screenPos);

        UseContext use_context = {
            player->controlledEntity,
            player->controlledEntity->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };

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
        print_line(get_parent()->get_multiplayer()->get_multiplayer_peer()->get_connection_status());
        print_line(get_parent()->get_multiplayer()->get_multiplayer_peer()->get_connection_status());

        Vector3 worldPos = screenToWorld(get_viewport()->get_mouse_position());

        UseContext use_context = {
            player->controlledEntity,
            player->controlledEntity->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };

        //TODO: Ability use indicators
        if(input_event_key->is_action_pressed("cast_ability_1"))
        {
            printf("Q press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_FIRST, use_context);
            rpc("ability_use_request", Mercenary::ABILITY_FIRST, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_2"))
        {
            printf("W press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_SECOND, use_context);
            rpc("ability_use_request", Mercenary::ABILITY_SECOND, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_3"))
        {
            printf("E press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_THIRD, use_context);
            rpc("ability_use_request", Mercenary::ABILITY_THIRD, Vector2(worldPos.x, worldPos.z), 0);
        }
        else if(input_event_key->is_action_pressed("cast_ability_4"))
        {
            printf("R press\n");
            //player->controlledEntity->use_ability(Mercenary::ABILITY_ULTIMATE, use_context);
            rpc("ability_use_request", Mercenary::ABILITY_ULTIMATE, Vector2(worldPos.x, worldPos.z), 0);
        }
    }
}

void Game::_on_connect_to_remote_game()
{
    Dictionary player_cfg;
    player_cfg["nickname"] = "Boris";
    //So apparently RPC won't be received by server unless rpc interface ticks at least once
    Error err = rpc("player_cfg_update_request", player_cfg);
    print_line("RPC err: ", err);
}


void Game::_bind_methods()
{
    //Global signals
    ADD_SIGNAL(MethodInfo(GameStringNames::get_singleton()->ON_DAMAGE_TAKEN, PropertyInfo(Variant::OBJECT, "entity"), PropertyInfo(Variant::OBJECT, "damage_object")));

    //Methods
    ClassDB::bind_method(D_METHOD("movement_request", "target_position", "target_entity_id"), &Game::movement_request);
    ClassDB::bind_method(D_METHOD("attack_request", "target_position"), &Game::attack_request);
    ClassDB::bind_method(D_METHOD("ability_use_request", "target_position"), &Game::ability_use_request);
    ClassDB::bind_method(D_METHOD("player_cfg_update_request", "target_position"), &Game::player_cfg_update_request);
}

Game::~Game()
{
    
}