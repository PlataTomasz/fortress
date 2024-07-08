#if !defined(ENTITY_NAME_DISPLAY_INCLUDED)
#define ENTITY_NAME_DISPLAY_INCLUDED

#include <scene/gui/label.h>

class Entity;

class EntityNameDisplay : public Label {
GDCLASS(EntityNameDisplay, Label);
private:
    Entity *ent = nullptr;

    void _update_text(const String& new_text);
    void _on_entity_change();
protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    void set_entity(Entity *p_ent) {
        ent = p_ent;
        _on_entity_change();
    }

    Entity *get_entity() {
        return ent;
    }
};

#endif // ENTITY_NAME_DISPLAY_INCLUDED
