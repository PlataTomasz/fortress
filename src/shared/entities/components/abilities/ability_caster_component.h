#if !defined(ABILITY_CASTER_COMPONENT_H_INCLUDED)
#define ABILITY_CASTER_COMPONENT_H_INCLUDED

#include <shared/entities/components/component.h>
#include <shared/data_holders/use_context.hpp>

class Ability;

/**
 * Ability caster component is a component which allows using abilities that are child of this component
*/
// TODO: Make editable in editor
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
    static void _bind_methods();
public:
    void set_ability(AbilitySetIndex abilityIndex, Ability *ability);
    void use_ability(AbilitySetIndex ability_id, UseContext use_context);
    void use_basic_attack(UseContext& use_context);

    void _notification(int notification);

    Error use_ability(int index, Dictionary use_context);

    virtual ~AbilityCasterComponent();

    AbilityCasterComponent();

};

#endif // ABILITY_CASTER_COMPONENT_H_INCLUDED
