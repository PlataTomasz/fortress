    #if !defined(BARBARIAN_DANCE_WITH_DEATH_INCLUDED)
#define BARBARIAN_DANCE_WITH_DEATH_INCLUDED

#include <shared/abilities/ability.hpp>

class BarbarianDanceWithDeath : public Ability{
GDCLASS(BarbarianDanceWithDeath, Ability);
private:

public:
    // 
    #ifdef CLIENT
    virtual void _clientside_use(const Ref<ActionContext>& action_context) override;
    #endif
    
    #ifdef SERVER
    virtual void _use(const Ref<ActionContext>& action_context) override;
    #endif
};

#endif // BARBARIAN_DANCE_WITH_DEATH_INCLUDED
