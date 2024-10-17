#if !defined(BARBARIAN_INTIMIDATING_CRY_ABILITY_INCLUDED)
#define BARBARIAN_INTIMIDATING_CRY_ABILITY_INCLUDED

#include <shared/abilities/ability.hpp>
#include <scene/resources/packed_scene.h>

class Area3D;

class BarbarianIntimidatingCryAbility : public Ability {
GDCLASS(BarbarianIntimidatingCryAbility, Ability);
private:
    Area3D *warcry_area = nullptr;
    Ref<PackedScene> warcry_vfx;
protected:
    void _use(const Ref<ActionContext> &use_context) override;
    static void _bind_methods();
public:
    void set_warcry_area(Area3D *new_warcry_area);
    Area3D *get_warcry_area();

    void set_warcry_vfx(const Ref<PackedScene> &new_vfx);
    Ref<PackedScene> get_warcry_vfx();
};

#endif // BARBARIAN_INTIMIDATING_CRY_ABILITY_INCLUDED
