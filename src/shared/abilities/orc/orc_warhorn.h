#if !defined(ORC_WARHORN_ABILITY)
#define ORC_WARHORN_ABILITY

#include <shared/abilities/ability.hpp>

class Area3D;

class OrcWarhornAbility : public Ability {
GDCLASS(OrcWarhornAbility, Ability);
private:
    Area3D *buff_hitarea = nullptr;
    Ref<AudioStream> warhorn_audio;
    Ref<PackedScene> warhorn_vfx;
protected:
    virtual void _use(const Ref<ActionContext> &action_context) override;
    static void _bind_methods();
public:
    void set_buff_hitarea(Area3D *new_buff_hitarea);
    Area3D *get_buff_hitarea();

    void set_warhorn_audio(const Ref<AudioStream> &audio_stream);
    Ref<AudioStream> get_warhorn_audio();

    void set_warhorn_vfx(const Ref<PackedScene> &new_warhorn_vfx);
    Ref<PackedScene> get_warhorn_vfx();
};

#endif // ORC_WARHORN_ABILITY
