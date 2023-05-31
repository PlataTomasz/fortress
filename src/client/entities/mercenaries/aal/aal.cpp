#include <client/entities/mercenaries/aal/aal.hpp>

#include <client/game_logic/abilities/test_ability.hpp>
#include <client/game_logic/abilities/aal/aal_chain_lightning.h>
#include <client/game_logic/abilities/aal/aal_strucked_twice.h>
#include <client/game_logic/abilities/aal/aal_straight_through_heart.h>

Aal::Aal()
{
    abilitySet[ABILITY_PASSIVE] = new TestAbility();
    abilitySet[ABILITY_FIRST] = new AalChainLightning();
    abilitySet[ABILITY_SECOND] = new TestAbility();
    abilitySet[ABILITY_THIRD] = new AalStruckedTwice();
    abilitySet[ABILITY_ULTIMATE] = new AalStraightThroughHeart();

    basic_attack_ability = new TestAbility();

    //abilitySet[ABILITY_PASSIVE] = new TestAbility();
    abilitySet[ABILITY_FIRST]->set_owner(this);
    //abilitySet[ABILITY_SECOND] = new TestAbility();
    abilitySet[ABILITY_THIRD]->set_owner(this);
    abilitySet[ABILITY_ULTIMATE]->set_owner(this);

}