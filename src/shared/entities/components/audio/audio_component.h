#if !defined(AUDIO_COMPONENT_INCLUDED)
#define AUDIO_COMPONENT_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/3d/audio_stream_player_3d.h>

class AudioEntry : public Resource {
GDCLASS(AudioEntry, Resource);
private:
    String name;
    Ref<AudioStream> stream;
protected:
    static void _bind_methods();
public:
    void set_stream_name(const String& new_name) {
        name = new_name;
    }

    String get_stream_name() {
        return name;
    }

    void set_stream(const Ref<AudioStream>& new_stream) {
        stream = new_stream;
    }

    Ref<AudioStream> get_stream() {
        return stream;
    }
};

class AudioComponent : public Node3D {
GDCLASS(AudioComponent, Node3D);
private:
    AudioStreamPlayer3D *audio_player = nullptr;

    TypedArray<AudioEntry> audio_entries;
protected:
    static void _bind_methods(); 
public:
    void play_defined_sound(const String& sound_name);

    void set_audio_entries(const TypedArray<AudioEntry>& new_audio_entries);
    TypedArray<AudioEntry> get_audio_entries();

    void set_audio_player(AudioStreamPlayer3D *new_audio_player);
    AudioStreamPlayer3D *get_audio_player();
};

#endif // AUDIO_COMPONENT_INCLUDED
