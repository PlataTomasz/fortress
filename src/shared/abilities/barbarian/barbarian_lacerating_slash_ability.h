#if !defined(BARBARIAN_LACERATING_SLASH_ABILITY_INCLUDED)
#define BARBARIAN_LACERATING_SLASH_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>

class Area3D;

class BarbarianLaceratingSlashAbility : public Ability {
GDCLASS(BarbarianLaceratingSlashAbility, Ability);
private:
    Area3D *slash_area = nullptr;
    Ref<PackedScene> slash_area_vfx;
    Ref<PackedScene> slash_hit_vfx;
    Ref<AudioStream> sword_swing_sound;
    Ref<AudioStream> hit_sound;
    
    float base_damage = 15;

    void _slash_hit_entity(Entity *entity);
protected:
    virtual void _use(const Ref<ActionContext> &use_context) override;
    static void _bind_methods();
public:
    void set_slash_area(Area3D *new_slash_area);
    Area3D *get_slash_area();

    void set_sword_swing_sound(const Ref<AudioStream> &new_sword_swing_sound);
    Ref<AudioStream> get_sword_swing_sound();

    void set_hit_sound(const Ref<AudioStream> &new_hit_sound);
    Ref<AudioStream> get_hit_sound();

    void set_slash_area_vfx(const Ref<PackedScene> &new_slash_area_vfx);
    Ref<PackedScene> get_slash_area_vfx();

    void set_slash_hit_vfx(const Ref<PackedScene> &new_slash_hit_vfx);
    Ref<PackedScene> get_slash_hit_vfx();

    void set_base_damage(float new_base_damage);
    float get_base_damage();

};

#endif // BARBARIAN_LACERATING_SLASH_ABILITY_INCLUDED
