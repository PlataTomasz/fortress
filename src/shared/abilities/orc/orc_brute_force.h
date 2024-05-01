#if !defined(ORC_BRUTE_FORCE_INCLUDED)
#define ORC_BRUTE_FORCE_INCLUDED

#include <shared/abilities/ability.hpp>

class OrcBruteForce : public Ability {
GDCLASS(OrcBruteForce, Ability);
protected:
    void _use(const Ref<ActionContext> &action_context);
};

#endif // ORC_BRUTE_FORCE_INCLUDED
