#include "mercenary.hpp"
#include <shared/abilities/test_ability.hpp>
#include <shared/helper_macros.h>

#include <shared/entities/components/movement/movement_component.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/entities/components/damage/damageable_component.h>

Mercenary::Mercenary()
{

}

Mercenary::~Mercenary()
{
    
}

void Mercenary::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("get_portrait_icon"), &Mercenary::get_portrait_icon);
    ::ClassDB::bind_method(D_METHOD("set_portrait_icon"), &Mercenary::set_portrait_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "portrait_icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_portrait_icon", "get_portrait_icon");
}

Node *Mercenary::_get_component(const String& component_typename) {
    if (component_typename == AbilityCasterComponent::get_class_static()) {
        return get_ability_caster_component();
    }
    if (component_typename == EntityAttributesComponent::get_class_static()) {
        return get_attributes_component();
    }
    if (component_typename == StatusEffectVictimComponent::get_class_static()) {
        return get_status_effect_victim_component();
    }
    if (component_typename == DamageableComponent::get_class_static()) {
        return get_damageable_component();
    }
    return nullptr;
}

Ref<Texture2D> Mercenary::get_portrait_icon() {
    return portrait_icon;
}

void Mercenary::set_portrait_icon(const Ref<Texture2D>& p_icon) {
    portrait_icon = p_icon;
}