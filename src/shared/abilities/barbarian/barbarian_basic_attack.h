#if !defined(BARBARIAN_BASIC_ATTACK_INCLUDED)
#define BARBARIAN_BASIC_ATTACK_INCLUDED

#include <core/object/ref_counted.h>
#include <shared/data_holders/action_context.hpp>

class Area3D;

class BarbarianBasicAttack {
private:
    float damage = 0;
    Area3D *hitbox = nullptr;
public:
    void use(const Ref<ActionContext>& use_context);

    
};

#endif // BARBARIAN_BASIC_ATTACK_INCLUDED
