#if !defined(STATUS_EFFECT_TOOLTIP_INCLUDED)
#define STATUS_EFFECT_TOOLTIP_INCLUDED

#include <scene/gui/panel_container.h>
#include <scene/gui/texture_rect.h>

// TODO: Might try different approach in the future than creating different tooltip class for each object that can have tooltip - Bridge Pattern?
class StatusEffectTooltip : public PanelContainer {
GDCLASS(StatusEffectTooltip, PanelContainer);
private:
    TextureRect *icon_display = nullptr;
    Label *tooltip_display = nullptr;
    Label *name_display = nullptr;
protected:
    static void _bind_methods();
public:
    TextureRect *get_icon_display() const { return icon_display; }
    void set_icon_display(TextureRect *icon_display_) { icon_display = icon_display_; }
    Label *get_tooltip_display() const { return tooltip_display; }
    void set_tooltip_display(Label *tooltip_display_) { tooltip_display = tooltip_display_; }
    Label *get_name_display() const { return name_display; }
    void set_name_display(Label *name_display_) { name_display = name_display_; }

};

#endif // STATUS_EFFECT_TOOLTIP_INCLUDED
