#if !defined(PLAYER_HUD_INCLUDED)
#define PLAYER_HUD_INCLUDED

#include <scene/gui/control.h>

class TextureRect;
class ProgressBar;
class Entity;
class Mercenary;
class StatusEffect;

/**
 * Class which purpose is to display Player's current Mercenary data, such as status effects, health, mana, abilities, etc.
*/
class PlayerHUD : public Control {
GDCLASS(PlayerHUD, Control);
private:
    Control *status_effect_area = nullptr;
    Control *ability_area = nullptr;
    Control *tooltip_area = nullptr;
    Control *current_tooltip = nullptr;

    ProgressBar *xp_bar = nullptr;
    ProgressBar *health_bar = nullptr;
    TextureRect *character_portrait = nullptr;

    void _ready();
    void _on_current_health_changed(float old_health, float new_health);

    void _on_controlled_mercenary_changed(Mercenary *old_mercenary, Mercenary *new_mercenary);

    // Controlled entity received a new StatusEffect
    void _on_self_status_effect_gain(StatusEffect *status_effect);
protected:
    void _notification(int p_notification);

    static void _bind_methods();
public:

    // Controlled entity's health changed
    void _on_self_health_changed(float p_health);

    void set_health_bar(ProgressBar *p_health_bar);
    ProgressBar *get_health_bar();

    void set_status_effect_area(Control *p_status_effect_area);
    Control *get_status_effect_area();

};

#endif // PLAYER_HUD_INCLUDED
