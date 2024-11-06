#if !defined(BARBARIAN_INTIMIDATING_CRY_ABILITY_INCLUDED)
#define BARBARIAN_INTIMIDATING_CRY_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>
#include <scene/resources/packed_scene.h>
#include <servers/audio/audio_stream.h>

class Area3D;

class BarbarianIntimidatingCryAbility : public Ability {
GDCLASS(BarbarianIntimidatingCryAbility, Ability);
private:
    Area3D *warcry_area = nullptr;
    Ref<PackedScene> warcry_vfx;
    Ref<AudioStream> intimidating_cry_use_sound;
protected:
    void _use(const Ref<ActionContext> &use_context) override;
    static void _bind_methods();
public:
    void set_warcry_area(Area3D *new_warcry_area);
    Area3D *get_warcry_area();

    void set_warcry_vfx(const Ref<PackedScene> &new_vfx);
    Ref<PackedScene> get_warcry_vfx();

    void set_intimidating_cry_use_sound(const Ref<AudioStream> &new_intimidating_cry_use_sound);
    Ref<AudioStream> get_intimidating_cry_use_sound();
};

#endif // BARBARIAN_INTIMIDATING_CRY_ABILITY_INCLUDED
