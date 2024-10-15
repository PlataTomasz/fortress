#include "orc_warhorn.h"

#include <scene/3d/physics/area_3d.h>
#include <core/variant/variant.h>
#include <shared/status_effects/status_effect.hpp>
#include <shared/core/managers/component_manager.h>
#include <shared/entities/components/status_effects/status_effect_victim_component.h>
#include <shared/registries/status_effect_registry.h>

void OrcWarhornAbility::set_buff_hitarea(Area3D *new_buff_hitarea) {
	buff_hitarea = new_buff_hitarea;
}

Area3D *OrcWarhornAbility::get_buff_hitarea() {
	return buff_hitarea;
}

void OrcWarhornAbility::_bind_methods() {
	::ClassDB::bind_method(D_METHOD("get_buff_hitarea"), &OrcWarhornAbility::get_buff_hitarea);
    ::ClassDB::bind_method(D_METHOD("set_buff_hitarea"), &OrcWarhornAbility::set_buff_hitarea);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "buff_hitarea", PROPERTY_HINT_NODE_TYPE, Area3D::get_class_static()), "set_buff_hitarea", "get_buff_hitarea");

	::ClassDB::bind_method(D_METHOD("get_warhorn_audio"), &OrcWarhornAbility::get_warhorn_audio);
    ::ClassDB::bind_method(D_METHOD("set_warhorn_audio"), &OrcWarhornAbility::set_warhorn_audio);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "warhorn_audio", PROPERTY_HINT_RESOURCE_TYPE, AudioStream::get_class_static()), "set_warhorn_audio", "get_warhorn_audio");

	::ClassDB::bind_method(D_METHOD("get_warhorn_vfx"), &OrcWarhornAbility::get_warhorn_vfx);
    ::ClassDB::bind_method(D_METHOD("set_warhorn_vfx"), &OrcWarhornAbility::set_warhorn_vfx);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "warhorn_vfx", PROPERTY_HINT_RESOURCE_TYPE, PackedScene::get_class_static()), "set_warhorn_vfx", "get_warhorn_vfx");
}

void OrcWarhornAbility::set_warhorn_audio(const Ref<AudioStream> &audio_stream) {
	warhorn_audio = audio_stream;
}

Ref<AudioStream> OrcWarhornAbility::get_warhorn_audio() {
	return warhorn_audio;
}

void OrcWarhornAbility::set_warhorn_vfx(const Ref<PackedScene> &new_warhorn_vfx) {
	warhorn_vfx = new_warhorn_vfx;
}

Ref<PackedScene> OrcWarhornAbility::get_warhorn_vfx() {
	return warhorn_vfx;
}