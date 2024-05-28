#if !defined(UI_INCLUDED)
#define UI_INCLUDED

#include <scene/gui/control.h>

class StatusEffectIndicator;
class StatusEffect;

class UI : public Control {
GDCLASS(UI, Control);
public:
    // Feels wrong, but don't know better approach
    static StatusEffectIndicator *create_status_effect_indicator(StatusEffect *for_status_effect);
};

#endif // UI_INCLUDED
