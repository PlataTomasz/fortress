#if !defined(ENTITY_HPP_INCLUDED)
#define ENTITY_HPP_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/3d/area_3d.h>

#include <core/string/ustring.h>
#include <core/templates/hash_map.h>
#include <core/templates/vector.h>
#include "../stats/stat_modifier.hpp"
#include "ability_charge_data.h"

#include <client/game_logic/damage_object.hpp>


class StatusEffect;
class MeshInstance3D;

/**
 * Object that is used to represent most of the beings on the GameMap
 *
 * @note Game logic happens in two dimensions, the third one is used ocassionally in special scenarios.
*/
class Entity : public Node3D
{
GDCLASS(Entity, Node3D);

enum FacingDirection
{
    FACING_DIRECTION_DOWN   =   0,
    FACING_DIRECTION_UP     =   180,
    FACING_DIRECTION_LEFT   =   -90,
    FACING_DIRECTION_RIGHT  =   90
};

public:
	struct Stats
	{
		//Defefnsive stats
        HealthStat health;
		Stat healthRegeneration;
		CompositeStat physicalResistance;
		CompositeStat magicResistance;
		//Damage reduction can be: magical, physical, global(any type of damage except true)
		Stat globalDamageReduction;
		Stat physicalDamageReduction;
		Stat magicDamageReduction;

		//Offensive
		CompositeStat physicalDamage;
		CompositeStat magicPower;
		CompositeStat attackRecovery;

		//Damage multipliers
		Stat globalDamageIncrease;
		Stat physicalDamageIncrease;
		Stat magicDamageIncrease;

		//Damage increases over time - per basic attack hit
		Stat rampup;

		//Healing from damage dealt
		Stat vamp;

		//Utility
		CompositeStat movementSpeed;
		Stat spellRecovery;

		CompositeStat resource;
		Stat resourceRegeneration;
	} stats;
protected:
    Area3D* hitbox;
    real_t hitbox_radius = 0.4;
    
    AbilityChargeData abilityChargeData;

    MeshInstance3D* model;

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

    bool alive = true;

    /**
     * Amount of units that entity should move by with every second of movement.
    */
    unsigned int movementSpeed = 2;

    // TODO: Implement different collision behaviours(for collision logic handling)

    virtual void movement_process_frame();

    /**
     * Amount of ticks that entity will be alive.
    */
    unsigned int maxLifetime = 100;
    unsigned int currLifetime = 0;
public:
    //Max 256 effects at the same time
    //Vector<StatusEffect*> appliedStatusEffects;
    HashMap<String, StatusEffect*> applied_status_effects;

public:
    bool is_alive();
    void kill(Entity* killer);

    void castAbility(int abilityId);

    //Called every physics frame
    void physics_frame();
    void _shared_ready();
    void ready();
    void on_collision(Area3D *collider);
    Area3D* get_hitbox();

    void take_damage(Ref<DamageObject> damage_object);

    void add_child_notify(Node* node) override;

    /**
     * Returns vector which describes where entity is facing
    */
    Vector2 get_facing_direction();
    real_t get_facing_direction_angle();

    bool remove_status_effect(String status_effect_name);
    bool remove_status_effect(StatusEffect* status_effect);
    StatusEffect* apply_status_effect(String status_effect_name, float duration, Entity *inflictor);
    StatusEffect* get_status_effect(String status_effect_name);
    bool has_status_effect(String status_effect_name);

    AbilityChargeData::Error start_charging_ability(IChargeable* ability);
protected:
    static void _bind_methods();
public:
    Entity();
    ~Entity();
};

#endif // ENTITY_HPP_INCLUDED
