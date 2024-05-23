#if !defined(STATUS_EFFECT_INDICATOR_INCLUDED)
#define STATUS_EFFECT_INDICATOR_INCLUDED

#include <scene/gui/control.h>

class Label;
class TextureRect;

class StatusEffectIndicator : public Control {
GDCLASS(StatusEffectIndicator, Control);
private:
    Label *name_label = nullptr;
    Label *description_label = nullptr;
    TextureRect *icon_display = nullptr;
protected:
    static void _bind_methods();
public:
    void set_displayed_name(const String& name);
    void set_displayed_description(const String& description);
    void set_displayed_icon(const Ref<Texture2D>& icon);

    Label *get_name_label();
    void set_name_label(Label *p_name_label);
    Label *get_description_label();
    void set_description_label(Label *p_description_label);
    TextureRect *get_icon_display();
    void set_icon_display(TextureRect *p_icon_display);
};

#endif // STATUS_EFFECT_INDICATOR_INCLUDED
