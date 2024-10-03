#if !defined(ABILITY_TOOLTIP_INCLUDED)
#define ABILITY_TOOLTIP_INCLUDED

#include <scene/gui/panel_container.h>
#include <scene/gui/texture_rect.h>
#include <scene/gui/label.h>

class Ability;

class AbilityTooltip : public PanelContainer {
GDCLASS(AbilityTooltip, PanelContainer);
private:
    Ability *ability = nullptr;

    TextureRect *ability_icon_display = nullptr;
    Label *ability_name_display = nullptr;
    Label *ability_description_display = nullptr;

    void _on_ability_change(Ability *new_ability);
protected:
    static void _bind_methods();
public:
    void set_ability(Ability *new_ability);
    Ability *get_ability();

    void set_ability_icon_display(TextureRect *new_ability_icon_display);
    TextureRect *get_ability_icon_display();
    
    void set_ability_name_display(Label *new_ability_name_display);
    Label *get_ability_name_display();

    void set_ability_description_display(Label *new_ability_description_display);
    Label *get_ability_description_display();
};

#endif // ABILITY_TOOLTIP_INCLUDED
