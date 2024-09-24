#if !defined(TURRET_INCLUDED)
#define TURRET_INCLUDED

#include <shared/entities/entity.h>
#include <shared/core/advanced_area_3d.h>

class Timer;

class Turret : public Entity {
GDCLASS(Turret, Entity);
private:
    Entity *current_target = nullptr;

    Timer *attack_cooldown_counter = nullptr;
    Node3D *turret_attack_origin_node = nullptr;

    AdvancedArea3D *aggro_area = nullptr;

    float cooldown_between_attacks = 0;
    
    void _on_target_left_aggro_area();
    void _on_entity_left_aggro_area(Entity *entity_that_left);
    void _on_entity_enter_aggro_area(Entity *entity_that_entered);

    Ref<PackedScene> projectile_template;

    void _attack_off_cooldown();
    void _on_death();
protected:
    void _initv() override;
    void _readyv() override;
    static void _bind_methods();
public:
    void attack_current_target();

    bool has_target();
    bool is_entity_valid_target(Entity *potential_target);
    Entity *get_higher_priority_target(Entity *first_entity, Entity *second_entity);
    Entity *get_closest_entity(const Vector<Entity *>& entities);

    Entity *find_new_target();
    int get_aggro_priority_for_entity(Entity *entity);
    void change_target(Entity *new_target);

    void set_aggro_area(AdvancedArea3D *new_aggro_area);
    AdvancedArea3D *get_aggro_area();

    void set_cooldown_between_attacks(float new_cooldown);
    float get_cooldown_between_attacks();

    void set_turret_attack_origin_node(Node3D *new_origin_node);
    Node3D *get_turret_attack_origin_node();

    void set_projectile_template(const Ref<PackedScene>& new_projectile_template);
    Ref<PackedScene> get_projectile_template();
};

#endif // TURRET_INCLUDED
