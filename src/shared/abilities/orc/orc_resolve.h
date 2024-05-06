#if !defined(ORC_RESOLVE_INCLUDED)
#define ORC_RESOLVE_INCLUDED

#include <shared/abilities/ability.hpp>
#include <shared/core/managers/component_manager.h>

class OrcResolve : public Ability {
GDCLASS(OrcResolve, Ability);
private:
    Entity *target = nullptr;
protected:
    void _notification(int p_notification);
public:
    void _tick();
};

#endif // ORC_RESOLVE_INCLUDED
