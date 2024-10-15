#if !defined(ORC_CRUSHING_BLOWS_BUFF_INCLUDED)
#define ORC_CRUSHING_BLOWS_BUFF_INCLUDED

#include <shared/status_effects/status_effect.hpp>

#include <shared/data_holders/damage_object.hpp>

class OrcCrushingBlowsBuff : public StatusEffect {
GDCLASS(OrcCrushingBlowsBuff, StatusEffect);
private:
    void _on_basic_attack_damage_dealt(const Ref<DamageObject> damage_object, Entity *target);
protected:
    void _on_apply() override;
    void _on_remove() override;
};

#endif // ORC_CRUSHING_BLOWS_BUFF_INCLUDED
