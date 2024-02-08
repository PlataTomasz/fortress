#include "level_component.h"

StringName LevelComponent::COMPONENT_NAME = StaticCString::create("level_component");

int LevelComponent::get_xp_to_next_level()
{
    if(current_level == LevelComponent::MAX_LEVEL)
    {
        //Indicates that we are already at our max level
        return 0;
    }
    else 
    {
        return current_level*xp_per_level - current_xp;
    }
}

int LevelComponent::get_required_xp(int level)
{
    if(level < LevelComponent::MAX_LEVEL && level > 0)
    {
        return level*xp_per_level;
    }
    else
    {
        //Level out of range - most likely max level is reached
        return 0;
    }
}

void LevelComponent::set_current_level(int new_level)
{
    if(new_level < LevelComponent::MAX_LEVEL && new_level > 0)
    {
        //Level in range - safe to set
        this->current_level = new_level;
        this->current_xp = get_required_xp(new_level);
    }
}