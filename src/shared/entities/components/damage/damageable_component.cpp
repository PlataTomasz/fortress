#include "damageable_component.h"
#include <shared/string_names/component_stringnames.h>
#include <shared/entities/node_methods.h>
#include <shared/entities/components/entity_stats/entity_stat_component.h>

void DamageableComponent::take_damage(Ref<DamageObject> damage_object)
{
    //Check if entity has component responsible for attributes

    Entity *ent = Object::cast_to<Entity>(get_parent());
    ERR_FAIL_NULL(ent);
    StatComponent *stat_component = ent->get_component<StatComponent>();
    ERR_FAIL_NULL(stat_component);

    if(unlikely(!stat_component)) return;
    //Apply modifiers
    emit_signal("pre_take_damage", damage_object);
    //Entity took damage and now it applies mitigation rules
    emit_signal("on_take_damage", damage_object);

    //Ref<Stat> health = stat_component.health;
    //Ref<Stat> defense = stat_component.global_defense;

    //Damage formula here

    emit_signal("post_take_damage", damage_object);
}