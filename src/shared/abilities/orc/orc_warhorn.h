#if !defined(ORC_WARHORN_ABILITY)
#define ORC_WARHORN_ABILITY

#include <shared/abilities/ability.hpp>

class OrcWarhornAbility : public Ability {
    virtual void use_impl();
};

#endif // ORC_WARHORN_ABILITY
