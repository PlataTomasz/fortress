#if !defined(STATUS_EFFECT_INDICATOR_INCLUDED)
#define STATUS_EFFECT_INDICATOR_INCLUDED

#include <scene/gui/control.h>
class StatusEffect;

class StatusEffectIndicator : public Control {
GDCLASS(StatusEffectIndicator, Control);
private:
    StatusEffect *status_effect = nullptr;
    Control *tooltip_object = nullptr;

    TextureRect *icon_display = nullptr;

    void _init();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void set_displayed_name(const String& name);
    void set_displayed_description(const String& description);
    void set_displayed_icon(const Ref<Texture2D>& icon);

    void set_tooltip_visible(bool p_visible);
    bool is_tooltip_visible();

    StatusEffect *get_status_effect() const;
    void set_status_effect(StatusEffect *status_effect_);

    TextureRect *get_icon_display();
    void set_icon_display(TextureRect *p_icon_display);
};

#endif // STATUS_EFFECT_INDICATOR_INCLUDED
