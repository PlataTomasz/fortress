#if !defined(ORC_WARHORN_ABILITY)
#define ORC_WARHORN_ABILITY

#include <shared/abilities/ability.hpp>

class OrcWarhornAbility : public Ability {
protected:
    void _use(const Ref<ActionContext>& action_context);

    static void _bind_methods();
};

#endif // ORC_WARHORN_ABILITY
