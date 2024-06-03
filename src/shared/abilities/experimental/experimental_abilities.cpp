#include "example_ability_01.h"

#include <shared/registries/entity_registry.h>
#include <shared/core/sh_game.h>
#include <shared/core/game_level.h>

Ability::AbilityUseError ExampleAbility01::use(const Ref<ActionContext>& use_context) {
    // Spawn box entity underneath user
    Entity *ent = use_context->get_user();

    Entity *box = Registry<Entity>::get_singleton()->create_instance("box_entity");
    box->set_position(ent->get_position());
    box->set_name(itos(box->get_instance_id()));
    Realm::get_shared_game()->get_current_level()->add_entity(box);
    return Ability::AbilityUseError::SUCCESS;
}
