#if !defined(ABILITY_CASTER_COMPONENT_H_INCLUDED)
#define ABILITY_CASTER_COMPONENT_H_INCLUDED

#include <shared/entities/components/component.h>
#include <shared/data_holders/use_context.hpp>

class Ability;

class AbilityCasterComponent : public Component
{
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
protected:
    /**
     * [0] - Passive
     * [1, 2, 3] - Other abilities
     * [4] - Ultimate
    */
    Ability *basic_attack_ability;
    Ability *abilitySet[AbilitySetIndex::ABILITY_MAX];

    static void _bind_methods();
public:
    void set_ability(AbilitySetIndex abilityIndex, Ability *ability);

    void use_ability(AbilitySetIndex ability_id, UseContext use_context);
    void use_basic_attack(UseContext& use_context);

    void _notification(int notification);

    void initialize();
    void tick();

    AbilityCasterComponent();
    AbilityCasterComponent(Ability *abilities[ABILITY_MAX]);

};

#endif // ABILITY_CASTER_COMPONENT_H_INCLUDED
