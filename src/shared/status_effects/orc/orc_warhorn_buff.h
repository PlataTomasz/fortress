#if !defined(ORC_WARHORN_BUFF_INCLUDED)
#define ORC_WARHORN_BUFF_INCLUDED

#include <shared/status_effects/status_effect.hpp>

class FloatValueModifier;

class OrcWarhornBuff : public StatusEffect {
GDCLASS(OrcWarhornBuff, StatusEffect);
private:
    FloatValueModifier *attack_speed_modifier = nullptr;
protected:
    void _on_apply() override;
    void _on_remove() override;
public:

};

#endif // ORC_WARHORN_BUFF_INCLUDED
