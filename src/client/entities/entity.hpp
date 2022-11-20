#if !defined(ENTITY_HPP_INCLUDED)
#define ENTITY_HPP_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/3d/area_3d.h>

#include "../status_effects/status_effect_manager.hpp"

#include <unordered_map>

using namespace godot;

/**
 * Object that is used to represent most of the beings on the GameMap
 * 
 * @note Game logic happens in two dimensions, the third one is used ocassionally in special scenarios.
*/
class Entity : public Node3D
{
GDCLASS(Entity, Node3D);

protected:
    enum Team
    {
        TEAM_NONE = 0,
        TEAM_RED = 1,
        TEAM_BLUE = 2
    };

    Team currentTeam;

    //START: RETHINK
    //TODO: Rethink
    enum Capablities
    {
        CAN_NOTHING = 0,

        CAN_MOVE = 1,
        CAN_CAST_SPELLS = 1<<1,
        CAN_USE_ITEMS = 1<<2,
        CAN_DASH = 1<<3,
        CAN_EVERYTHING = 1<<15
    };

    /**
     * Bitmask representing what Entity can perform.
    */
    unsigned short abilityMask;
    //END: RETHINK

    /**
     * Amount of units that entity should move by with every second of movement.
    */
    unsigned int movementSpeed = 2;

    // TODO: Implement different collision behaviours(for collision logic handling)

    virtual void movementProcess();

    /**
     * Amount of ticks that entity will be alive.
    */
    unsigned int maxLifetime = 100;
    unsigned int currLifetime = 0;

    //Max 256 effects at the same time
    std::unordered_map<String, StatusEffect*> statusEffects;

public:
    void castAbility(int abilityId);

    //Called every physics frame
    void physics_frame();
    void ready();
    void onCollision(Area3D *collider);

    StatusEffectManager::Error applyStatusEffect(String statusEffectName, float durration, Entity *inflictor);
    bool hasStatusEffect(String statusEffectName);
protected:
    static void _bind_methods(){};
public:
    Entity();
    ~Entity();
};

#endif // ENTITY_HPP_INCLUDED