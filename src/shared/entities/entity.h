#if !defined(ENTITY_INCLUDED)
#define ENTITY_INCLUDED

#include <scene/3d/node_3d.h>
#include <scene/main/multiplayer_api.h>
#include <server/server.h>

class GameLevel;
class EntityBehaviourProvider;
class StatusEffectVictimComponent;
class DamageableComponent;
class AbilityCasterComponent;
class EntityAttributesComponent;
class MovementComponent;
/**
 * Base class for representing most of the in-game objects, such as projectiles, monsters, ticking entities
 */
class Entity : public Node3D {
GDCLASS(Entity, Node3D);
private:
	// Components
	EntityBehaviourProvider *behaviour = nullptr;
	StatusEffectVictimComponent *status_effect_victim_component = nullptr;
    DamageableComponent *damageable_component = nullptr;
	AbilityCasterComponent *ability_caster_component = nullptr;
	EntityAttributesComponent *attributes_component = nullptr;
	MovementComponent *movement_component = nullptr;

	// Name which is displayed by the UI
	String displayed_name;

	void _init();
	void _ready();
	void _tick();

	void _exit_tree();


protected:
	virtual Node *_get_component(const String& component_typename);

	void _notification(int p_notification);

	static void _bind_methods();

	virtual void _initv() {};
	virtual void _readyv() {};
	virtual void _tickv() {};
public:
	bool has_tag(const String& tag);
	void add_tag(const String& tag);
	void remove_tag(const String& tag);

	StatusEffectVictimComponent *get_status_effect_victim_component();
    void set_status_effect_victim_component(StatusEffectVictimComponent *new_status_effect_vicitm_component);
    DamageableComponent *get_damageable_component();
    void set_damageable_component(DamageableComponent *new_damageable_component);
	AbilityCasterComponent *get_ability_caster_component();
    void set_ability_caster_component(AbilityCasterComponent *new_ability_caster_component);
	EntityAttributesComponent *get_attributes_component();
    void set_attributes_component(EntityAttributesComponent *new_attributes_component);
	MovementComponent *get_movement_component();
    void set_movement_component(MovementComponent *new_movement_component);

	Vector2 get_position_2d() {
		Vector3 pos = get_position();
		return Vector2(pos.x, pos.z);
	}

	float get_rotation_2d() {
		return get_rotation().y;
	}

	String get_displayed_name() {
		return displayed_name;
	}

	void set_displayed_name(const String& p_displayed_name) {
		displayed_name = p_displayed_name;
		emit_signal("displayed_name_changed", p_displayed_name);
	}

	// Returns level where this entity is
	GameLevel *get_gamelevel();

	Entity() {
	}

	
	template<class T>
	T *get_component() {
		return Object::cast_to<T>(_get_component(T::get_class_static()));
	}
};

#endif // ENTITY_INCLUDED
