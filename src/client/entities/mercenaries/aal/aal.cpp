#include <client/entities/mercenaries/aal/aal.hpp>

#include <client/game_logic/abilities/test_ability.hpp>
#include <client/game_logic/abilities/aal/aal_discharge.hpp>
#include <client/game_logic/abilities/aal/aal_chain_lightning.h>
#include <client/game_logic/abilities/aal/aal_static_void.h>
#include <client/game_logic/abilities/aal/aal_strucked_twice.h>
#include <client/game_logic/abilities/aal/aal_straight_through_heart.h>
#include <client/game_logic/abilities/empty_ability.h>

Aal::Aal()
{
    //Abilities
    set_ability(ABILITY_PASSIVE, memnew(AalDischarge));
    set_ability(ABILITY_FIRST, memnew(TestAbility));
    set_ability(ABILITY_SECOND, memnew(TestAbility));
    set_ability(ABILITY_THIRD, memnew(TestAbility));
    set_ability(ABILITY_ULTIMATE, memnew(TestAbility));
}