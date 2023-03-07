#if !defined(ENTITY_STATUS_BAR_HPP_INCLUDED)
#define ENTITY_STATUS_BAR_HPP_INCLUDED

#include <classes/sprite3d.hpp>
#include <classes/progress_bar.hpp>

using namespace godot;

/**
 * Node responsible for displaying entity status above each entity
*/
class EntityStatusBar3D : public Sprite3D
{
GDCLASS(EntityStatusBar3D, Sprite3D);

    static void _bind_methods();
private:
    ProgressBar* health_bar;
    ProgressBar* resource_bar;

    void on_health_amount_change(float value);
    void on_resource_amount_change(float value);
public:
    void _ready() override;
    void _enter_tree() override;

    EntityStatusBar3D();
};

#endif // ENTITY_STATUS_BAR_HPP_INCLUDED