#if !defined(STATUS_EFFECT_HPP)
#define STATUS_EFFECT_HPP

#include <core/string/ustring.h>
#include <core/variant/dictionary.h>
#include <core/variant/variant.h>
#include <cstdio>
#include <scene/3d/node_3d.h>

class Entity;
class StatusEffectVictimComponent;

//Class which acts as a template for instantiating new status effect instances
//NOTE: Name is set by StatusEffectManager
class StatusEffect : public Node3D
{
GDCLASS(StatusEffect, Node3D);
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
    String displayed_name;
    String displayed_description;
    Ref<Texture2D> icon;
    Entity *inflictor = nullptr;

    int max_stacks = 1;
    int current_stacks = 1;

    // How many stacks are lost when effect timer runs out?
    int stacks_loss = 1;

    float max_duration = 10;
    float current_duration = 10;
    StatusEffect::Type type;

    bool permament = true;

protected:
    // Script Overrideable methods
    GDVIRTUAL0(_on_apply)
    GDVIRTUAL0(_on_remove)
    GDVIRTUAL0(_tick)
    GDVIRTUAL0(_tick_internal)

    virtual void _on_remove();
    virtual void _on_apply();

    void _notification(int p_notification);

    static void _bind_methods();
public:
    StatusEffectVictimComponent *get_victim_component();
    Entity *get_victim_entity();

    String get_displayed_name();
    void set_displayed_name(const String& p_name);
    String get_displayed_description();
    void set_displayed_description(const String& p_description);
    Ref<Texture2D> get_icon();
    void set_icon(const Ref<Texture2D>& p_icon);

    //Permament effects are those which max_duration is -1. That also includes effect that expire under certain conditions(like leaving slowing area)
    bool is_permament();
    void set_permament(bool p_permament);

    int get_current_stacks();
    void set_current_stacks(int stacks);

    int get_max_stacks();
    void set_max_stacks(int p_stacks);

    //TODO: Maybe return value, informing that stack was not added and why?
    void add_stacks();

    void refresh();

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
