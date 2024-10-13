#if !defined(REGISTER_CLIENTSIDE_TYPES_INCLUDED)
#define REGISTER_CLIENTSIDE_TYPES_INCLUDED

#include <client/ui/buttons/disconnect_from_server_button.h>
#include <client/ui/game/abilities/ability_button.h>
#include <client/ui/game/abilities/ability_tooltip.h>
#include <client/ui/game/turret/turret_recharge_indicator.h>

void register_clientside_types() {
    ClassDB::register_class<DisconnectFromServerButton>();
    ClassDB::register_class<ActiveAbilityButton>();
    ClassDB::register_class<AbilityTooltip>();
    ClassDB::register_class<TurretRechargeIndicator>();
}

#endif // REGISTER_CLIENTSIDE_TYPES_INCLUDED
