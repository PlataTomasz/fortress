#if !defined(ENTITY_HEALTH_BAR_INCLUDED)
#define ENTITY_HEALTH_BAR_INCLUDED

#include <scene/gui/texture_progress_bar.h>
#include <scene/gui/progress_bar.h>
#include <shared/entities/entity.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <scene/gui/label.h>

/**
 * 
 */
class EntityHealthBar : public TextureProgressBar {
GDCLASS(EntityHealthBar, TextureProgressBar);
private:
    // Entity, which this health bar is displayed for
    Entity *ent = nullptr;
    Label *_value_indicator = nullptr;

    void _on_current_health_changed(float new_value) {
        set_value(Math::ceil(new_value));
        ERR_FAIL_NULL(_value_indicator);
        String value_indicator_text = vformat("%d/%d", get_value(), get_max());
        _value_indicator->set_text(value_indicator_text);
    }

    void _update_healthbar() {
        ERR_FAIL_NULL(ent);
        // Initialize displayed health bar value
        EntityAttributesComponent *attributes = ent->get_attributes_component();
        ERR_FAIL_NULL_MSG(attributes, "Entity is missing attributes component. EntityHealthBar cannot work without it!");

        // BUG: For some unknown for me reason, an invalid attribute is returned if called outside ready. Possibly a refactor of set_entity is needed.
        Ref<CappedFloatAttribute> health_attribute = attributes->get_health();
        ERR_FAIL_NULL(health_attribute);

        health_attribute->connect("current_value_changed", callable_mp(this, &EntityHealthBar::_on_current_health_changed));
        print_line("EntityHealthBar::_update_healthbar::ent:", ent->to_string());
        print_line("EntityHealthBar::_update_healthbar::health_attribute:",health_attribute->to_string());

        float curr_hp = health_attribute->get_current();
        float max_hp = health_attribute->get_max();

        set_max(max_hp);
        set_value(curr_hp);

        ERR_FAIL_NULL(_value_indicator);
        String indicator_text = vformat(" %d / %d", curr_hp, max_hp);
        _value_indicator->set_text(indicator_text);
    }
protected:
    void _notification(int p_notification);
    static void _bind_methods();
public:
    void set_value_visible(bool p_value_visible) {
        ERR_FAIL_NULL(_value_indicator);
        _value_indicator->set_visible(p_value_visible);
    }

    bool is_value_visible() {
        ERR_FAIL_NULL_V(_value_indicator, false);
        return _value_indicator->is_visible();
    }

    void set_value_indicator(Label *p_label) {
        _value_indicator = p_label;
    }

    Label *get_value_indicator() {
        return _value_indicator;
    }
    
    void set_entity(Entity *p_ent) {
        ent = p_ent;
        // Update health bar after change
        DISABLE_IN_EDITOR();
        _update_healthbar();
    }

    Entity *get_entity() {
        return ent;
    }
};

#endif // ENTITY_HEALTH_BAR_INCLUDED
