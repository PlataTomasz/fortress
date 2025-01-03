#include "damageable_component.h"
#include <shared/string_names/component_stringnames.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/core/managers/component_manager.h>
#include <shared/core/realm.h>
#include <shared/core/sh_game.h>
#include <shared/gamemodes/gamemode.h>
#include <shared/data_holders/damage_object.hpp>
#include <shared/entities/entity.h>

#include <shared/networking/rpc/rpc_config_builder.h>
#include <shared/networking/rpc/rpc_registerer.h>

void DamageableComponent::take_damage(Ref<DamageObject> damage_object) {
    if(!is_damageable_by(damage_object)) return;
    if(is_dead()) return;

    Entity *owning_entity = get_owning_entity();
    ERR_FAIL_NULL(owning_entity);

    EntityAttributesComponent *attributes_component = owning_entity->get_attributes_component();
    if(!attributes_component) return;

	float global_defense_value = attributes_component->get_global_defense()->get_current();

    Ref<CappedResourceAttribute> health_atr = attributes_component->get_health();
	float health_value = health_atr->get_current();

	//Reduce incoming damage with global defense - Damage reduction equation
	float damage_taken_multiplier = 100 / (100 + global_defense_value);
	float incoming_damage = damage_taken_multiplier * damage_object->get_value();

    health_atr->set_current(health_value - incoming_damage);

	bool was_lethal = attributes_component->get_health()->get_current() <= 0;
	emit_signal("damage_taken", damage_object);

	if (was_lethal) {
        rpc("server_rpc_death");
		emit_signal("death", damage_object);
        print_line(get_owning_entity(), "died!");
	}
}

bool DamageableComponent::is_damageable_by(Ref<DamageObject> damage_object) {
    SH_Game *game = Realm::get_shared_game();
    ERR_FAIL_NULL_V(game, false);

    Gamemode *gamemode = game->get_gamemode();
    ERR_FAIL_NULL_V(gamemode, false);

    if(gamemode->is_entity_enemy_of(get_owning_entity(), damage_object->get_attacker()) || damage_object->is_self_damage()) {
        return true;
    } else {
        return false;
    }
}

void DamageableComponent::heal(float value) {
    Entity *ent = get_owning_entity();
    ERR_FAIL_NULL(ent);
    
    EntityAttributesComponent *attributes = ent->get_component<EntityAttributesComponent>();

    Ref<CappedResourceAttribute> health_attribute = attributes->get_health();

    float max_health = health_attribute->get_max();
    float current_health = health_attribute->get_current();

    // Make sure heal won't exceed maximum life
    float heal_value = (value + current_health) > max_health ? max_health - current_health : value;

    health_attribute->set_current(current_health + heal_value);
}

Entity *DamageableComponent::get_owning_entity() {
    return Object::cast_to<Entity>(get_parent());
}

void DamageableComponent::_bind_methods() {
    ADD_SIGNAL(MethodInfo("damage_taken", PropertyInfo(Variant::OBJECT, "damage_object")));
    ADD_SIGNAL(MethodInfo("death", PropertyInfo(Variant::OBJECT, "damage_object", PROPERTY_HINT_RESOURCE_TYPE, DamageObject::get_class_static())));
    ADD_SIGNAL(MethodInfo("revived"));

    ClassDB::bind_method(D_METHOD("server_rpc_death"), &DamageableComponent::server_rpc_death);
    ClassDB::bind_method(D_METHOD("server_rpc_revive"), &DamageableComponent::server_rpc_revive);
}

bool DamageableComponent::is_dead() {
    Entity *ent = get_owning_entity();
    ERR_FAIL_NULL_V(ent, false);
    EntityAttributesComponent *attribute_component = ent->get_attributes_component();
    ERR_FAIL_NULL_V(attribute_component, false);
    return !(attribute_component->get_health()->get_current() > 0);
}



void DamageableComponent::set_dead(bool new_state) {
    dead = new_state;
}

void DamageableComponent::_notification(int p_notification) {
    switch (p_notification)
    {
    case NOTIFICATION_READY:
        {
            RPCRegisterer(this, "server_rpc_death", 
                RPCConfigBuilder()
                    .rpc_mode(MultiplayerAPI::RPC_MODE_AUTHORITY)
                    .transfer_mode(MultiplayerPeer::TRANSFER_MODE_RELIABLE)
                    .channel(0)
                    .call_local(false)
                    .build()
                );
            
            RPCRegisterer(this, "server_rpc_revive", 
                RPCConfigBuilder()
                    .rpc_mode(MultiplayerAPI::RPC_MODE_AUTHORITY)
                    .transfer_mode(MultiplayerPeer::TRANSFER_MODE_RELIABLE)
                    .channel(0)
                    .call_local(false)
                    .build()
                );
        }
        break;
    
    default:
        break;
    }
}