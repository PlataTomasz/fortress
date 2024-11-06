#include "barbarian_dance_with_death.h"

#include <shared/registries/status_effect_registry.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/entities/components/visual/visual_component_3d.h>
#include <shared/entities/components/audio/audio_component.h>

#ifdef SERVER
void BarbarianDanceWithDeath::_use(const Ref<ActionContext>& action_context) {
    const static String USE_ANIMATION_NAME = "Warcry001"; 

    Entity *ent = action_context->get_user();
    ERR_FAIL_NULL(ent);
    
    StatusEffectVictimComponent *status_effect_component = ent->get_component<StatusEffectVictimComponent>();
    ERR_FAIL_NULL(status_effect_component);

    VisualComponent3D *visual_component = ent->get_visual_component();
    if(visual_component) {
        visual_component->play_animation_override(USE_ANIMATION_NAME);
    } else {
        print_error("Failed to play animation " + USE_ANIMATION_NAME + "!");
    }

    StatusEffect *status_effect = Registry<StatusEffect>::get_singleton()->create_instance("dance_with_death");
    status_effect->set_inflictor(action_context->get_user()); // TODO: There has to be a better way of doing this, than setting manualy...

    ERR_FAIL_NULL(status_effect);
    status_effect_component->apply_status_effect(status_effect);
}
#endif

#ifdef CLIENT

void BarbarianDanceWithDeath::_use(const Ref<ActionContext>& action_context) {
    ERR_FAIL_NULL(action_context->get_user());
    // Play sound
    AudioComponent *audio_component = action_context->get_user()->get_audio_component();
    if(audio_component) {
        audio_component->play_defined_sound("warcry");
    } else {
        print_error("Failed to play sound! Missing AudioComponent!");
    }

    play_vfx(action_context, use_vfx);

    // Play animation
    VisualComponent3D *visual_component = action_context->get_user()->get_visual_component();
    if(visual_component)  {
        visual_component->play_animation_override("warcry");
    }
    else {
        print_error("Failed to play sound! Missing VisualComponent3D!");
    }
    
    // Play VFX

}

#endif

void BarbarianDanceWithDeath::set_use_vfx(const Ref<PackedScene> &new_use_vfx) {
    use_vfx = new_use_vfx;
}

Ref<PackedScene> BarbarianDanceWithDeath::get_use_vfx() {
    return use_vfx;
}

void BarbarianDanceWithDeath::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_use_vfx"), &BarbarianDanceWithDeath::get_use_vfx);
    ClassDB::bind_method(D_METHOD("set_use_vfx", "use_vfx"), &BarbarianDanceWithDeath::set_use_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "use_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_use_vfx", "get_use_vfx");
}