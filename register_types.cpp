/*************************************************************************/
/*  register_types.cpp                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "register_types.h"

#ifdef CLIENT
#include <client/game.h>
#include <client/client.hpp>
#include <client/game_camera.hpp>
#include <client/ui/user_interface.h>
#include <client/ui/character_select_elem.h>
#include <client/ui/main_menu.h>
#endif

#ifdef SERVER
#include <server/server.h>
#include <server/core/game.h>
#endif

#include <shared/core/game_level.h>
#include <shared/entities/entity.h>
#include <shared/entities/mercenaries/mercenary.hpp>
#include <shared/entities/mercenaries/lemon/lemon.h>
#include <shared/entities/mercenaries/orange/orange.h>
#include <shared/entities/components/component.h>
#include <shared/entities/components/entity_stats/entity_attributes_component.h>
#include <shared/entities/components/damage/damageable_component.h>
#include <shared/entities/components/movement/movement_component.h>
#include <shared/entities/components/visual/visual_component_3d.h>

#include <shared/abilities/orc/orc_resolve.h>
#include <shared/abilities/orc/orc_leap_slam.h>
#include <shared/abilities/orc/orc_warhorn.h>

#include <shared/registries/status_effect_registry.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/status_effects/example/slow_status_effect.h>

#include <client/ui/player_hud.h>
#include <client/ui/status_effect_indicator.h>
#include <client/ui/game/status_effect_tooltip.h>

#include <shared/registries/mercenary_registry.h>

#include <shared/abilities/experimental/example_ability_01.h>
#include <shared/abilities/barbarian/barbarian_dance_with_death.h>
#include <shared/abilities/barbarian/barbarian_basic_attack.h>
#include <shared/abilities/barbarian/barbarian_bleeding_passive.h>

#include <shared/status_effects/barbarian/dance_with_death_status.h>
#include <shared/status_effects/example/bleeding_status_effect.h>


void initialize_artifact_seekers_module(ModuleInitializationLevel p_level)
{
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }

#ifdef CLIENT
	ClassDB::register_class<Client>();
	ClassDB::register_class<GameCamera>();
    ClassDB::register_class<UserInterface>();
    ClassDB::register_class<CharacterSelectElem>();
    //Currently broken - temporarily disabled
	//ClassDB::register_class<EntityStatusBar3D>();

    ClassDB::register_class<PlayerHUD>();
    ClassDB::register_class<StatusEffectIndicator>();
    ClassDB::register_class<StatusEffectTooltip>();
    ClassDB::register_class<MainMenu>();
#endif

#ifdef SERVER
	//Server classes - needed for build with locally hosted server
	ClassDB::register_class<Server>();
#endif
    // Abilities
    ClassDB::register_class<Ability>();
        // Examples
        ClassDB::register_class<ExampleAbility01>();
	// Shared
    
    ClassDB::register_class<Game>();
    ClassDB::register_class<GameLevel>();
    ClassDB::register_class<Entity>();
    ClassDB::register_class<Component>();
    ClassDB::register_class<EntityAttributesComponent>();
    ClassDB::register_class<DamageableComponent>();
    ClassDB::register_class<HitboxComponent>();
    ClassDB::register_class<FloatAttribute>();
    ClassDB::register_class<FloatValueModifier>();
    ClassDB::register_class<MovementComponent>();
    ClassDB::register_class<VisualComponent3D>();
    ClassDB::register_class<Mercenary>();
        ClassDB::register_class<Orange>();
        ClassDB::register_class<Lemon>();

    ClassDB::register_class<Player>();
    ClassDB::register_class<MovementComponent>();

    ClassDB::register_class<AbilityCasterComponent>();
    ClassDB::register_class<StatusEffectVictimComponent>();

    // Registries
    //ClassDB::register_class<StatusEffectRegistry>();
    ClassDB::register_class<MercenaryRegistry>();
    
    // Orc abilities
    ClassDB::register_class<OrcResolve>();
    ClassDB::register_class<OrcLeapSlam>();
    ClassDB::register_class<OrcWarhornAbility>();

    // Barbarian abilities
    ClassDB::register_class<BarbarianBasicAttack>();
    ClassDB::register_class<BarbarianBleedingPassive>();
    ClassDB::register_class<BarbarianDanceWithDeath>();

    //ClassDB::register_class<>();

    // Attributes
    ClassDB::register_class<Attribute>();
    ClassDB::register_class<FloatAttribute>();
    ClassDB::register_class<CappedFloatAttribute>();
    ClassDB::register_class<CappedResourceAttribute>();

    ClassDB::register_class<FloatValueModifier>();

    // Status Effects
    ClassDB::register_class<StatusEffect>();
    ClassDB::register_class<SlowStatusEffect>();
    ClassDB::register_class<DanceWithDeathStatus>();
    ClassDB::register_class<BleedingStatusEffect>();

    // Singletons
    //Engine::get_singleton()->add_singleton(Engine::Singleton("MercenaryRegistry", MercenaryRegistry::get_singleton()));
}

void uninitialize_artifact_seekers_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
