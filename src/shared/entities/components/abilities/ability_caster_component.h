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
    Array ability_paths;
public:
    Array get_ability_paths();
    void set_ability_paths(const Array &new_ability_paths);
    
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
    Ability *get_passive_ability();

    void set_ability(AbilitySetIndex abilityIndex, Ability *ability){};
    Ability::AbilityUseError use_ability(int index, const Ref<ActionContext>& action_context);
    void use_basic_attack(const Ref<ActionContext>& action_context){};

    void _notification(int notification);

    virtual ~AbilityCasterComponent();

    AbilityCasterComponent();

};

#endif // ABILITY_CASTER_COMPONENT_H_INCLUDED
