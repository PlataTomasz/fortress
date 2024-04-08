#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>
#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <cstdio>
#include <scene/main/node.h>
#include <shared/core/systems/gameplay/gameplay_attributes.h>
#include <shared/core/systems/gameplay/gameplay_tags.h>

class Entity;
class StatusEffectVictimComponent;

//Class which acts as a template for instantiating new status effect instances
//NOTE: Name is set by StatusEffectManager
class StatusEffect : public Node
{
public:
    //GameplayAttributes attributes;
    PackedStringArray tags;

    // Every StatusEffect have this data
    enum Type
    {
        MISC,
        BUFF,
        DEBUFF,
        TYPE_MAX
    };
private:
    int max_stacks = 1;
    int current_stacks = 1;

    // How many stacks are lost when effect timer runs out?
    int stacks_loss = 1;

    float max_duration = 0;
    float current_duration = 0;
    StatusEffect::Type type;

    String tooltip = "default_status_effect_tooltip";
    Ref<Texture2D> icon;

    bool permament = true;

protected:
    // Script Overrideable methods
    GDVIRTUAL0(_on_apply)
    GDVIRTUAL0(_on_remove)
    GDVIRTUAL0(_tick)
    GDVIRTUAL0(_tick_internal)

    void _notification(int p_notification);

    static void _bind_methods();
public:
    StatusEffectVictimComponent *get_victim_component();
    Node *get_victim_entity();

    //Permament effects are those which max_duration is -1. That also includes effect that expire under certain conditions(like leaving slowing area)
    bool is_permament();
    void set_permament(bool p_permament);

    int get_current_stacks();
    void set_current_stacks(int stacks);

    int get_max_stacks();
    void set_max_stacks(int p_stacks);

    //TODO: Maybe return value, informing that stack was not added and why?
    void add_stacks(int stack_count, bool refresh = true);

    void refresh();

    void _on_remove();
    void _on_apply();
    void _tick();
    void _tick_internal();

    // This status effect is queued for deletion
    void expire();

    operator String() const;

    //WARN: DO NOT USE !!! Should be used only for engine register purpose.
    //NOTE: Maybe just make this class abstract and instantiable only by StatusEffectManager?
    StatusEffect()
    {
        
    }

    friend class Entity;
    friend class StatusEffectManager;
};

VARIANT_ENUM_CAST(StatusEffect::Type);

//TODO: Maybe implement It with Nodes(create StatusEffectInstance class?)
#endif // STATUS_EFFECT_HPP
