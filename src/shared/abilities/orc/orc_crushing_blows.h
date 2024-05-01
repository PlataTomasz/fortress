#if !defined(ORC_CRUSHING_BLOWS_INCLUDED)
#define ORC_CRUSHING_BLOWS_INCLUDED

#include <shared/abilities/ability.hpp>

class OrcCrushingBlows : public Ability {
GDCLASS(OrcCrushingBlows, Ability);
protected:
    void _use(const Ref<ActionContext> &action_context);
};

#endif // ORC_CRUSHING_BLOWS_INCLUDED
