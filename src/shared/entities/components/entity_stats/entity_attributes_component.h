#if !defined(ENTITY_STATS_INCLUDED)
#define ENTITY_STATS_INCLUDED

#include <scene/main/node.h>
#include "float_attribute.h"

class EntityAttributesComponent : public Node
{
GDCLASS(EntityAttributesComponent, Node);
private:

protected:
    static void _bind_methods();
public:
    Ref<CappedResourceAttribute> health = memnew(CappedResourceAttribute(100, 0, 100));
    //Reduces damage no matter damage type
    Ref<FloatAttribute> global_defense = memnew(FloatAttribute(30));
    Ref<FloatAttribute> attack_damage = memnew(FloatAttribute(75));
    Ref<FloatAttribute> attack_speed = memnew(FloatAttribute(1.0));
    Ref<FloatAttribute> magic_power = memnew(FloatAttribute(0));
    Ref<FloatAttribute> cooldown_reduction = memnew(FloatAttribute(0));
    Ref<FloatAttribute> movement_speed = memnew(FloatAttribute(300));

    Ref<FloatAttribute> get_health();
    void set_health(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_global_defense();
    void set_global_defense(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_attack_damage();
    void set_attack_damage(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_attack_speed();
    void set_attack_speed(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_magic_power();
    void set_magic_power(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_cooldown_reduction();
    void set_cooldown_reduction(Ref<FloatAttribute> attribute);
    Ref<FloatAttribute> get_movement_speed();
    void set_movement_speed(Ref<FloatAttribute> attribute);

    EntityAttributesComponent() {
        
    }
};

#endif // ENTITY_STATS_INCLUDED