#if !defined(ENTITY_HPP_INCLUDED)
#define ENTITY_HPP_INCLUDED

#include <classes/node3d.hpp>
#include <classes/area3d.hpp>

#include <variant/string.hpp>
#include <templates/hash_map.hpp>
#include <templates/vector.hpp>
#include "../stats/stat_modifier.hpp"

using namespace godot;

class StatusEffect;

/**
 * Object that is used to represent most of the beings on the GameMap
 *
 * @note Game logic happens in two dimensions, the third one is used ocassionally in special scenarios.
*/
class Entity : public Node3D
{
GDCLASS(Entity, Node3D);

private:
	struct Stats
	{
		//Defefnsive stats
		BaseBonusStat health;
		Stat healthRegeneration;
		BaseBonusStat physicalResistance;
		BaseBonusStat magicResistance;
		//Damage reduction can be: magical, physical, global(any type of damage except true)
		Stat globalDamageReduction;
		Stat physicalDamageReduction;
		Stat magicDamageReduction;

		//Offensive
		BaseBonusStat physicalDamage;
		BaseBonusStat magicPower;
		BaseBonusStat attackRecovery;

		//Damage multipliers
		Stat globalDamageIncrease;
		Stat physicalDamageIncrease;
		Stat magicDamageIncrease;

		//Damage increases over time - per basic attack hit
		Stat rampup;

		//Healing from damage dealt
		Stat vamp;

		//Utility
		BaseBonusStat movementSpeed;
		Stat spellRecovery;

		BaseBonusStat resource;
		Stat resourceRegeneration;
	};

	Stats stats;

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
public:
    //Max 256 effects at the same time
    //Vector<StatusEffect*> appliedStatusEffects;
    HashMap<String, StatusEffect*> appliedStatusEffects;

public:
    void castAbility(int abilityId);

    //Called every physics frame
    void _physics_process(double delta) override;
    void _ready() override;
    void onCollision(Area3D *collider);

    bool removeStatusEffect(String statusEffectName);
    StatusEffect* applyStatusEffect(String statusEffectName, float duration, Entity *inflictor);
    StatusEffect* getStatusEffect(String statusEffectName);
    bool hasStatusEffect(String statusEffectName);
protected:
    static void _bind_methods();
public:
    Entity();
    ~Entity();
};

#endif // ENTITY_HPP_INCLUDED
