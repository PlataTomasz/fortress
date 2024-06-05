#include "mercenary.hpp"
#include <shared/abilities/test_ability.hpp>
#include <shared/helper_macros.h>

#include <shared/entities/components/movement/movement_component.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>

Mercenary::Mercenary()
{

}

Mercenary::~Mercenary()
{
    
}

void Mercenary::_bind_methods() {
    //void (Mercenary::*x)() = &Mercenary::exampleTraitMethod;
    //ClassDB::bind_method(D_METHOD("exampleTraitMethod"), method_pointer_fix<Mercenary>(&Mercenary::exampleTraitMethod));

    TUsesAbilities::_bind_trait<Mercenary>();
    THasAttributes::_bind_trait<Mercenary>();

    ::ClassDB::bind_method(D_METHOD("get_status_effect_victim_component"), &Mercenary::get_status_effect_victim_component);
    ::ClassDB::bind_method(D_METHOD("set_status_effect_victim_component"), &Mercenary::set_status_effect_victim_component);
    ::ClassDB::add_property(get_class_static(), PropertyInfo(Variant::OBJECT, "status_effect_victim_component", PROPERTY_HINT_NODE_TYPE, "StatusEffectVictimComponent"), "set_status_effect_victim_component", "get_status_effect_victim_component");

    ::ClassDB::bind_method(D_METHOD("get_portrait_icon"), &Mercenary::get_portrait_icon);
    ::ClassDB::bind_method(D_METHOD("set_portrait_icon"), &Mercenary::set_portrait_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "portrait_icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_portrait_icon", "get_portrait_icon");
}

Node *Mercenary::_get_component(const String& component_typename) {
    if (component_typename == ability_caster_component->get_class()) {
        return ability_caster_component;
    }
    if (component_typename == attributes_component->get_class()) {
        return attributes_component;
    }
    if (component_typename == status_effect_victim_component->get_class()) {
        return status_effect_victim_component;
    }
    return nullptr;
}

StatusEffectVictimComponent *Mercenary::get_status_effect_victim_component() {
    return status_effect_victim_component;
}

void Mercenary::set_status_effect_victim_component(StatusEffectVictimComponent *p_status_effect_vicitm_component) {
    status_effect_victim_component = p_status_effect_vicitm_component;
}

Ref<Texture2D> Mercenary::get_portrait_icon() {
    return portrait_icon;
}

void Mercenary::set_portrait_icon(const Ref<Texture2D>& p_icon) {
    portrait_icon = p_icon;
}