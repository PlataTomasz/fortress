#if !defined(ORC_BRUTE_FORCE_INCLUDED)
#define ORC_BRUTE_FORCE_INCLUDED

#include <shared/abilities/ability.hpp>
#include <scene/resources/packed_scene.h>

class Area3D;

class OrcBruteForce : public Ability {
GDCLASS(OrcBruteForce, Ability);
private:
    Area3D *brute_force_area = nullptr;
    float hit_damage = 15;
    Ref<PackedScene> brute_force_vfx;
protected:
    void _use(const Ref<ActionContext> &action_context);
    static void _bind_methods();
public:
    void set_brute_force_area(Area3D *new_area);
    Area3D *get_brute_force_area();

    void set_hit_damage(float new_hit_damage);
    float get_hit_damage();

    void set_brute_force_vfx(const Ref<PackedScene> &new_brute_force_vfx);
    Ref<PackedScene> get_brute_force_vfx();
};

#endif // ORC_BRUTE_FORCE_INCLUDED
