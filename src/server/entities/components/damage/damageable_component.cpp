#include "damageable_component.h"

void take_damage(Ref<DamageObject> damage_object)
{
    if(unlikely(!stat_component)) return; 
    //Apply modifiers
    emit_signal("pre_take_damage", damage_object);
    //Entity took damage and now it applies mitigation rules
    emit_signal("on_take_damage", damage_object);

    Ref<Stat> health = stat_component.health;
    Ref<Stat> defense = stat_component.global_defense;

    //Damage formula: 

    emit_signal("post_take_damage", damage_object);
}