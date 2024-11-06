#if !defined(ABILITY_CASTER_COMPONENT_H_INCLUDED)
#define ABILITY_CASTER_COMPONENT_H_INCLUDED

#include <shared/entities/components/component.h>
#include <core/object/ref_counted.h>
#include <shared/data_holders/action_context.hpp>
#include <shared/abilities/ability.hpp>
#include <core/templates/vector.h>
#include <core/string/node_path.h>

class BasicAttack;

/**
 * Ability caster component is a component which allows using abilities that are child of this component
*/
// TODO: Make editable in editor
class AbilityCasterComponent : public Node3D
{
GDCLASS(AbilityCasterComponent, Node3D);
private:
    // Ability, which is currently being used, set back to nullptr when ability use is finished
    Ability *currently_used_ability = nullptr;

    BasicAttack *attack = nullptr;

    Ability *passive_ability = nullptr;    
    Ability *first_ability = nullptr;
    Ability *second_ability = nullptr;
    Ability *third_ability = nullptr;
    Ability *ultimate_ability = nullptr;

    void server_rpc_ability_used(int which_ability, Dictionary networked_action_data);
    void server_rpc_attack_used(Dictionary networked_action_data);

    void _on_ability_use_started(Ability *ability);
    void _on_ability_use_finished(Ability *ability);
    void _on_basic_attack_use_started(Ability *basic_attack);
    void _on_basic_attack_use_finished(Ability *basic_attack);

    void _ready();
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
    void _notification(int p_notification);
    static void _bind_methods();
public:
    Entity *get_owning_entity();

    void set_basic_attack(BasicAttack *p_basic_attack);
    BasicAttack *get_basic_attack();

    void set_passive_ability(Ability *p_passive_ability);
    Ability *get_passive_ability();

    void set_first_ability(Ability *p_ability);
    Ability *get_first_ability();

    void set_second_ability(Ability *p_ability);
    Ability *get_second_ability();

    void set_third_ability(Ability *p_ability);
    Ability *get_third_ability();

    void set_ultimate_ability(Ability *p_ability);
    Ability *get_ultimate_ability();

    void use_ability(int index, const Ref<ActionContext>& action_context);
    void use_basic_attack(const Ref<ActionContext>& action_context);

    Ability *get_ability_by_index(int index);

    virtual ~AbilityCasterComponent();

    AbilityCasterComponent();

};

VARIANT_ENUM_CAST(AbilityCasterComponent::AbilitySetIndex);

#endif // ABILITY_CASTER_COMPONENT_H_INCLUDED
