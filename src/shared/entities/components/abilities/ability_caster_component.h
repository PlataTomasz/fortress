#if !defined(ABILITY_CASTER_COMPONENT_H_INCLUDED)
#define ABILITY_CASTER_COMPONENT_H_INCLUDED

#include <shared/entities/components/component.h>
#include <core/object/ref_counted.h>
#include <shared/data_holders/action_context.hpp>
#include <shared/abilities/ability.hpp>
#include <core/templates/vector.h>
#include <core/string/node_path.h>

/**
 * Ability caster component is a component which allows using abilities that are child of this component
*/
// TODO: Make editable in editor
class AbilityCasterComponent : public Node3D
{
GDCLASS(AbilityCasterComponent, Node3D);
private:
    Ability *passive_ability;
    
    Ability *first_ability = nullptr;
    Ability *second_ability = nullptr;
    Ability *third_ability = nullptr;
    Ability *ultimate_ability = nullptr;
public:
    enum AbilitySetIndex  : int
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
    void set_first_ability(Ability *p_ability);
    Ability *get_first_ability();

    void set_second_ability(Ability *p_ability);
    Ability *get_second_ability();

    void set_third_ability(Ability *p_ability);
    Ability *get_third_ability();

    void set_ultimate_ability(Ability *p_ability);
    Ability *get_ultimate_ability();

    Ability *get_passive_ability();

    Ability::AbilityUseError use_ability(int index, const Ref<ActionContext>& action_context);
    void use_basic_attack(const Ref<ActionContext>& action_context){};

    void _notification(int notification);

    virtual ~AbilityCasterComponent();

    AbilityCasterComponent();

};

VARIANT_ENUM_CAST(AbilityCasterComponent::AbilitySetIndex);

#endif // ABILITY_CASTER_COMPONENT_H_INCLUDED
