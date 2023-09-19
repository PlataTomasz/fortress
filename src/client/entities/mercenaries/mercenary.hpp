#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include <client/entities/moving_entity.hpp>
#include <client/game_logic/abilities/ability.hpp>

/**
 * Mercenary is a class responsible for representing
 * specialization of entity which is primarily supposed
 * to be controlled by Player.
*/
class Mercenary : public MovingEntity
{
GDCLASS(Mercenary, MovingEntity);
public:
    enum AbilitySetIndex
    {
        ABILITY_PASSIVE = 0,
        ABILITY_FIRST,
        ABILITY_SECOND,
        ABILITY_THIRD,
        ABILITY_ULTIMATE,
        ABILITY_MAX
    };

private:
    
protected:
    /**
     * [0] - Passive
     * [1, 2, 3] - Other abilities
     * [4] - Ultimate
    */
    Ability* basic_attack_ability;
    Ability* abilitySet[AbilitySetIndex::ABILITY_MAX];

    int xp = 0;
    int level = 1;

    static void _bind_methods();
public:
    //Character level
    void set_level(int new_level);
    int get_level();

    //Experience 
    void set_xp(int new_xp);
    int get_xp();

    void set_ability(AbilitySetIndex abilityIndex, Ability *ability);

    void use_ability(AbilitySetIndex ability_id, UseContext use_context);
    void use_basic_attack(UseContext& use_context);

    void _notification(int notification);

    void initialize();
    void tick();

    Mercenary(Ability *abilities[AbilitySetIndex::ABILITY_MAX]);

    Mercenary();
    ~Mercenary();
};

#endif // MERCENARY_HPP_INCLUDED