#if !defined(ENTITY_STATUS_BAR_HPP_INCLUDED)
#define ENTITY_STATUS_BAR_HPP_INCLUDED

#include <scene/3d/sprite_3d.h>
#include <scene/gui/progress_bar.h>



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

    void on_health_change();
    void on_resource_change(float value);
public:
    void ready();
    void tree_entered();

    EntityStatusBar3D();
};

#endif // ENTITY_STATUS_BAR_HPP_INCLUDED