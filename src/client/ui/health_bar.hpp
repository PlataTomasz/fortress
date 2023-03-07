#if !defined(HEALTH_BAR_HPP_INCLUDE)
#define HEALTH_BAR_HPP_INCLUDE

#include <classes/progress_bar.hpp>

using namespace godot;

class EntityHealthBar : public ProgressBar
{
    static void _bind_methods();

public:
    void _ready();

    void update_value(float value);
    void update_position(Vector2 new_pos);
};

#endif // HEALTH_BAR_HPP_INCLUDE
