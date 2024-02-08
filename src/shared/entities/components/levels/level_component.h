#if !defined(LEVEL_COMPONENT_INCLUDED)
#define LEVEL_COMPONENT_INCLUDED

#include <shared/entities/components/component.h>

//Component responsible for entity expierience level
class LevelComponent : public Component
{
public:
    //Use component name in object metadata to speed-up access to components/check if object has component
    static StringName COMPONENT_NAME;
protected:
    int current_xp = 0;
    const static int MAX_LEVEL = 16;
    int current_level = 1;
    //How much XP is needed to reach next level, multiplier by current level
    //XP curve/array of XP values for next level could do better
    int xp_per_level = 250;
public:
    //Changes current xp level
    //NOTE: Also alters current_xp
    void set_current_level(int new_level);
    int get_current_level();

    //Experience 
    void set_current_xp(int new_xp);
    int get_current_xp();

    //Returns how much xp is needed to level-up
    int get_xp_to_next_level();
    int get_required_xp(int level);
    
};

#endif // LEVEL_COMPONENT_INCLUDED
