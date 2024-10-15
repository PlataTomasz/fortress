#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

#include <shared/data_holders/action_context.hpp>
#include <core/object/ref_counted.h>
#include <core/string/ustring.h>
#include <shared/helpers/object_ptr.h>

#include <core/string/node_path.h>
#include <servers/audio/audio_stream.h>

class Timer;
class AbilityCasterComponent;

/**
 * Class responsible for logic and data behind Abilities of mercenaries, items, etc.
*/
class Ability : public Node3D
{
GDCLASS(Ability, Node3D);
public:
    enum WhereToLookBeforeUse {
        KEEP_CURRENT,
        AT_TARGET_POSITION,
        AT_TARGET_ENTITY
    };
protected:

    // Internal use: Without most checks
    virtual void _use(const Ref<ActionContext>& action_context){};

    void play_sound(const Ref<ActionContext> &action_context, const Ref<AudioStream> &sound_resource);
    void play_animation(const Ref<ActionContext> &action_context, const String &animation_name);
    void play_vfx(const Ref<ActionContext> &action_context, const Ref<PackedScene> &vfx_scene);
private:
    WhereToLookBeforeUse where_to_look_at;
    // MovementComponent should pause movement until this ability finishes if true
    bool locks_movement = true;

    float _use_time = 0;

    class LookAtBehaviour {
    public:
        virtual void look(const Ref<ActionContext>& action_context) = 0; 
    };

    class UnchangedLookingAtCurrentBehaviour : public LookAtBehaviour{
    public:
        virtual void look(const Ref<ActionContext>& action_context) override {
            // Do nothing
        }
    } _unchanged_look_at_behaviour;

    class LookAtEntityBehaviour : public LookAtBehaviour {
    public:
        virtual void look(const Ref<ActionContext>& action_context) override {
            ERR_FAIL_NULL(action_context->get_target_entity());
            ERR_FAIL_NULL(action_context->get_user());
            action_context->get_user()->look_at(action_context->get_target_entity()->get_global_position(), Vector3(0,1,0), true);
        } 
    } _at_target_entity_look_at_behaviour;

    class LookAtTargetPositionBehaviour : public LookAtBehaviour {
    public:
        virtual void look(const Ref<ActionContext>& action_context) override {
            ERR_FAIL_NULL(action_context->get_user());
            action_context->get_user()->look_at(action_context->get_target_position(), Vector3(0,1,0), true);
        }
    } _at_target_position_look_at_behaviour;

    void _before_ability_use(const Ref<ActionContext>& action_context);

    void _init();
    LookAtBehaviour *_get_where_to_look_behaviour();
    void _instant_use(const Ref<ActionContext>& action_context);
    void _deferred_use_handler(const Ref<ActionContext>& action_context);
public:
    Timer *cooldown_timer = nullptr;
protected:
    void _notification(int p_notification);

    float max_cooldown = 0;

    Ref<Texture2D> icon;

    String displayed_name;
    String displayed_description;

    static void _bind_methods();

    void _on_ability_cooldown_finished();

    void start_ability_cooldown();
    void _handle_look_at(const Ref<ActionContext>& action_context);

    void _deferred_use(const Ref<ActionContext>& action_context);
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

    void set_where_to_look_at(WhereToLookBeforeUse new_where_to_look_at);
    WhereToLookBeforeUse get_where_to_look_at();
    
    void set_use_time(float new_use_time);
    float get_use_time();

    void set_locks_movement(bool new_locks_movement);
    bool is_locks_movement();

    void use(const Ref<ActionContext>& action_context);

    bool can_be_used(const Ref<ActionContext>& action_context);
    Ability();
};

VARIANT_ENUM_CAST(Ability::WhereToLookBeforeUse);

#endif // ABILITY_HPP_INCLUDED
