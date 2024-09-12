#if !defined(ACTIVE_ABILITY_BUTTON_INCLUDED)
#define ACTIVE_ABILITY_BUTTON_INCLUDED

#include <scene/gui/panel_container.h>

class Ability;
class TextureProgressBar;

class ActiveAbilityButton : public PanelContainer {
GDCLASS(ActiveAbilityButton, PanelContainer);
private:
    Ability *ability = nullptr;
    TextureProgressBar *progress_bar = nullptr;
    Label *value_indicator = nullptr;

    Timer *cooldown_timer = nullptr;

    void _on_ability_change(Ability *new_ability);
    void _init();
    void _process_frame();
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void set_indicator_icon(const Ref<Texture2D>& new_icon);

    void set_indicator_max_value(float max_value);
    void set_indicator_current_value(float current_value);

    void set_ability(Ability *new_ability);
    Ability *get_ability();

    void set_progress_bar(TextureProgressBar *new_progress_bar);
    TextureProgressBar *get_progress_bar();

    void set_value_indicator(Label *new_value_indicator);
    Label *get_value_indicator();

};

#endif // ACTIVE_ABILITY_BUTTON_INCLUDED