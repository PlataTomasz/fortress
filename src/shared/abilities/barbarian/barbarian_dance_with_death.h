    #if !defined(BARBARIAN_DANCE_WITH_DEATH_INCLUDED)
#define BARBARIAN_DANCE_WITH_DEATH_INCLUDED

#include <shared/abilities/ability.hpp>

class BarbarianDanceWithDeath : public Ability{
GDCLASS(BarbarianDanceWithDeath, Ability);
private:
    Ref<PackedScene> use_vfx;
protected:
    static void _bind_methods();
public:
    void set_use_vfx(const Ref<PackedScene> &new_use_vfx);
    Ref<PackedScene> get_use_vfx();

    // 
    #ifdef CLIENT
    virtual void _use(const Ref<ActionContext>& action_context) override;
    #endif
    
    #ifdef SERVER
    virtual void _use(const Ref<ActionContext>& action_context) override;
    #endif
};

#endif // BARBARIAN_DANCE_WITH_DEATH_INCLUDED
