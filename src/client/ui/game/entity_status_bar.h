#if !defined(ENTITY_STATUS_BAR_INCLUDED)
#define ENTITY_STATUS_BAR_INCLUDED

#include <scene/gui/flow_container.h>

class Entity;
class StatusEffect;

class EntityStatusBar : public HFlowContainer {
GDCLASS(EntityStatusBar, HFlowContainer);
private:
    Entity *ent = nullptr;

    void _on_status_effect_gain(StatusEffect *status_effect);
    void _on_status_effect_removed(StatusEffect *status_effect);

    void _update_status_bar();
protected:
    static void _bind_methods();
public:
    void set_entity(Entity *p_ent) {
        ent = p_ent;
        _update_status_bar();
    }

    Entity *get_entity() {
        return ent;
    }
};

#endif // ENTITY_STATUS_BAR_INCLUDED
