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

Game::Game()
{
    //Register signals
    if(!Engine::get_singleton()->is_editor_hint())
    {
        //Allow node to process inputs
        set_process_unhandled_input(true);
        set_process(true);
        printf("%d\n", is_processing_unhandled_input());

        connect("ready", callable_mp(this, &Game::ready));

        initialize_registries();
    }
}

Game::~Game()
{
    
}

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

void Game::put_sync_event(C_SyncEvent *sync_event)
{
    sync_events.push_back(sync_event);
}

void Game::ready()
{
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
        //TODO: Load map from file - currently left in undefined state
        std::cout<<"Camera was not loaded!"<<std::endl;
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

            player->controlledEntity->use_basic_attack(use_context);
        }
        else if(input_event_mouse_btn->is_action_pressed("movement"))
        {
            std::cout<<"MOVEMENT_ACTION"<<std::endl;
            player->controlledEntity->set_movement_target_position(worldPos);
            
            C_MovementGameRequest game_command = C_MovementGameRequest(0, Vector2(worldPos.x, worldPos.z));
            PackedByteArray bytes = game_command.serialize();
            client->send_data_to_server(bytes.ptr(), bytes.size());
        }
    }
    else if(const InputEventKey *input_event_key = Object::cast_to<InputEventKey>(event.ptr()))
    {
        Vector3 worldPos = screenToWorld(get_viewport()->get_mouse_position());

        UseContext use_context = {
            player->controlledEntity,
            player->controlledEntity->get_position(),
            Vector<Vector3>({worldPos}),
            Vector<Entity*>()
        };

        if(input_event_key->is_action_pressed("cast_ability_1"))
        {
            printf("Q press\n");
            player->controlledEntity->use_ability(Mercenary::ABILITY_FIRST, use_context);
        }
        else if(input_event_key->is_action_pressed("cast_ability_2"))
        {
            printf("W press\n");
            player->controlledEntity->use_ability(Mercenary::ABILITY_SECOND, use_context);
        }
        else if(input_event_key->is_action_pressed("cast_ability_3"))
        {
            printf("E press\n");
            player->controlledEntity->use_ability(Mercenary::ABILITY_THIRD, use_context);
        }
        else if(input_event_key->is_action_pressed("cast_ability_4"))
        {
            printf("R press\n");
            player->controlledEntity->use_ability(Mercenary::ABILITY_ULTIMATE, use_context);
        }
    }
}

void Game::_bind_methods()
{   
    //Global signals
    ADD_SIGNAL(MethodInfo(GameStringNames::get_singleton()->ON_DAMAGE_TAKEN, PropertyInfo(Variant::OBJECT, "entity"), PropertyInfo(Variant::OBJECT, "damage_object")));
}