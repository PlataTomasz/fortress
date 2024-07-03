#if !defined(STATUS_EFFECT_INDICATOR_INCLUDED)
#define STATUS_EFFECT_INDICATOR_INCLUDED

#include <scene/gui/control.h>

class StatusEffect;
class StatusEffectTooltip;
class TextureRect;

class StatusEffectIndicator : public Control {
GDCLASS(StatusEffectIndicator, Control);
private:
    StatusEffect *status_effect = nullptr;
    StatusEffectTooltip *tooltip_object = nullptr;

    TextureRect *icon_display = nullptr;

    void _init();

    bool tooltip_enabled = true;
    void _change_tooltip_visibility(bool p_visibility);
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    // Initializes indicator data from status effect
    void initialize(StatusEffect *p_status_effect);

    void set_icon(const Ref<Texture2D>& p_icon);

    StatusEffectTooltip *get_tooltip_object();
    void set_tooltip_object(StatusEffectTooltip *p_tooltip);

    StatusEffect *get_status_effect() const;
    void set_status_effect(StatusEffect *status_effect_);

    TextureRect *get_icon_display();
    void set_icon_display(TextureRect *p_icon_display);

    bool is_tooltip_enabled() {
        return tooltip_enabled;
    }

    void set_tooltip_enabled(bool p_tooltip_enabled) {
        tooltip_enabled = p_tooltip_enabled;
    }
};

#endif // STATUS_EFFECT_INDICATOR_INCLUDED
