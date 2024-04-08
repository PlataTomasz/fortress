#if !defined(ENTITY_STATS_INCLUDED)
#define ENTITY_STATS_INCLUDED

#include <scene/main/node.h>
#include "float_attribute.h"

class EntityAttributesComponent : public Node
{
GDCLASS(EntityAttributesComponent, Node);
private:
    
protected:
    static void _bind_methods(){};
public:
    Ref<FloatAttribute> current_health;
    Ref<FloatAttribute> max_health;
    //Reduces damage no matter damage type
    Ref<FloatAttribute> global_defense;
    Ref<FloatAttribute> attack_damage;
    Ref<FloatAttribute> attack_speed;
    Ref<FloatAttribute> magic_power;
    Ref<FloatAttribute> cooldown_reduction;
    Ref<FloatAttribute> max_cooldown_reducation;
    Ref<FloatAttribute> movement_speed;

    Ref<FloatAttribute> get_current_health();
    void set_current_health(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_max_health();
    void set_max_health(Ref<FloatAttribute> attribute);    
    Ref<FloatAttribute> get_global_defense();
    void set_global_defense(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_attack_damage();
    void set_attack_damage(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_attack_speed();
    void set_attack_speed(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_magic_power();
    void set_magic_power(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_damage_rampup();
    void set_damage_rampup(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_max_damage_rampup();
    void set_max_damage_rampup(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_cooldown_reduction();
    void set_cooldown_reduction(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_max_cooldown_reduction();
    void set_max_cooldown_reduction(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_movement_speed();
    void set_movement_speed(Ref<FloatAttribute> attribute);

    EntityAttributesComponent() {
        
    }
};

#endif // ENTITY_STATS_INCLUDED