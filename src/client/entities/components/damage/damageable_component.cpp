#include <shared/entities/components/damage/damageable_component.h>

void DamageableComponent::server_rpc_death() {
    // FIXME: Currently DamageObject contains invalid data, just to match signal method signature
    emit_signal("death", memnew(DamageObject(DamageObject::DamageType::DAMAGE_MAGICAL, DamageObject::DamageSubtype::NONE, 0, nullptr)));
}

void DamageableComponent::server_rpc_revive() {
    emit_signal("revived");
}

void DamageableComponent::revive() {
    ERR_FAIL_MSG("Not implemented!");
}