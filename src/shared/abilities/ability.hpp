#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include <shared/data_holders/action_context.hpp>
#include <core/object/ref_counted.h>
#include <core/string/ustring.h>
#include <shared/helpers/object_ptr.h>

#include <core/string/node_path.h>

class Timer;
class AbilityCasterComponent;

/**
 * Class responsible for logic and data behind Abilities of mercenaries, items, etc.
*/
class Ability : public Node3D
{
GDCLASS(Ability, Node3D);
#ifdef SERVER
protected:
    void _notification(int p_notification);

    // Internal use: Without most checks
    virtual void _use(const Ref<ActionContext>& action_context){};
#endif

#ifdef CLIENT
    virtual void _clientside_use(const Ref<ActionContext>& action_context){};
#endif
private:
    void _init();
public:
    Timer *cooldown_timer = nullptr;
protected:
    float max_cooldown = 0;

    Ref<Texture2D> icon;

    String displayed_name;
    String displayed_description;

    static void _bind_methods();

    void _on_ability_cooldown_finished();

    void start_ability_cooldown();
public:
    AbilityCasterComponent *get_ability_caster();

    void set_current_cooldown(float new_cooldown);
    float get_current_cooldown();

    float get_max_cooldown();
    void set_max_cooldown(float new_cooldown);

    bool is_on_cooldown();

    Ref<Texture2D> get_icon();
    void set_icon(const Ref<Texture2D> &new_icon);

    String get_displayed_description();
    void set_displayed_description(const String &new_description);

    String get_displayed_name();
    void set_displayed_name(const String &new_name);

    void use(const Ref<ActionContext>& action_context);
    Ability();
};

#endif // ABILITY_HPP_INCLUDED
