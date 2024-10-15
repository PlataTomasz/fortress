#include "audio_component.h"

#include <servers/audio/audio_stream.h>

void AudioEntry::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_stream_name"), &AudioEntry::get_stream_name);
    ClassDB::bind_method(D_METHOD("set_stream_name", "stream_name"), &AudioEntry::set_stream_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "stream_name"), "set_stream_name", "get_stream_name");

    ClassDB::bind_method(D_METHOD("get_stream"), &AudioEntry::get_stream);
    ClassDB::bind_method(D_METHOD("set_stream", "stream"), &AudioEntry::set_stream);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stream", PROPERTY_HINT_RESOURCE_TYPE, AudioStream::get_class_static()), "set_stream", "get_stream");
}

void AudioComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_audio_entries"), &AudioComponent::get_audio_entries);
    ClassDB::bind_method(D_METHOD("set_audio_entries", "audio_entries"), &AudioComponent::set_audio_entries);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "audio_entries", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT(AudioEntry::get_class_static())), "set_audio_entries", "get_audio_entries");

    ClassDB::bind_method(D_METHOD("get_audio_player"), &AudioComponent::get_audio_player);
    ClassDB::bind_method(D_METHOD("set_audio_player", "audio_player"), &AudioComponent::set_audio_player);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "audio_player", PROPERTY_HINT_NODE_TYPE, AudioStreamPlayer3D::get_class_static()), "set_audio_player", "get_audio_player");
}

void AudioComponent::set_audio_entries(const TypedArray<AudioEntry>& new_audio_entries) {
    audio_entries = new_audio_entries;
}

TypedArray<AudioEntry> AudioComponent::get_audio_entries() {
    return audio_entries;
}

void AudioComponent::set_audio_player(AudioStreamPlayer3D *new_audio_player) {
    audio_player = new_audio_player;
}

AudioStreamPlayer3D *AudioComponent::get_audio_player() {
    return audio_player;
}

void AudioComponent::play_defined_sound(const String& sound_name) {
    for(int i = 0;i<audio_entries.size();i++) {
        AudioEntry *audio_entry = Object::cast_to<AudioEntry>(audio_entries[i].operator Object*());
        ERR_CONTINUE(!audio_entry);

        if(audio_entry->get_stream_name() == sound_name) {
            ERR_FAIL_NULL(audio_player);

            audio_player->set_stream(audio_entry->get_stream());
            audio_player->play();

            break;
        }
    }
}

void AudioComponent::play_audio_stream(const Ref<AudioStream> &audio_stream) {
    ERR_FAIL_NULL(audio_player);
    audio_player->set_stream(audio_stream);
    audio_player->play();
}