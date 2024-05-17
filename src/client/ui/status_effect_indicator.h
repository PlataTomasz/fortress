#if !defined(STATUS_EFFECT_INDICATOR_INCLUDED)
#define STATUS_EFFECT_INDICATOR_INCLUDED

#include <scene/gui/control.h>
class StatusEffect;

class StatusEffectIndicator : public Control {
private:
    StatusEffect *status_effect = nullptr;
public:
    StatusEffect *get_status_effect() const;
    void set_status_effect(StatusEffect *status_effect_);

    Control *make_custom_tooltip(const String &p_text) const override;
};

#endif // STATUS_EFFECT_INDICATOR_INCLUDED
