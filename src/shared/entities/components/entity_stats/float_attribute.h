#if !defined(FLOAT_ATTRIBUTE_INCLUDED)
#define FLOAT_ATTRIBUTE_INCLUDED

#include "attribute.h"

class FloatValueModifier : public Resource{
GDCLASS(FloatValueModifier, Resource);
public:
	enum Type {
		FLAT_ADD = 0,
		MULTI_ADD = 1,
		MULTI_MUL = 2,
		ATTR_MOD_TYPE_MAX
	};
private:
	float value = 0;
	Type type = FLAT_ADD;
protected:
	static void _bind_methods();
public:
	void set_value(float p_value) { value = p_value; };
		float get_value() { return value; };

	void set_type(Type p_type) {
		type = p_type;
	}

	Type get_type() { 
		return type;
	}

	void expire() {
		emit_signal("on_expire", this);
	};

	FloatValueModifier(){};
};

// Numerical attribute
class FloatAttribute : public Attribute {
GDCLASS(FloatAttribute, Attribute);
protected:
	float base = 0;
	List<Ref<FloatValueModifier>> modifiers;
	float current = 0;

	static void _bind_methods();
public:

	// Recalculates current value - Mostly called when a modifier has expired
	void _recalculate() {
		// Recalculate current - might be different now
		float flat_modifier = 0;
		float additive_multiplier = 1;
		float multiplicative_multiplier = 1;

		for (Ref<FloatValueModifier> modifier : modifiers) {
			switch (modifier->get_type()) {
				case FloatValueModifier::Type::FLAT_ADD:
					flat_modifier += modifier->get_value();
					break;

				case FloatValueModifier::Type::MULTI_ADD:
					additive_multiplier += modifier->get_value();
					break;

				case FloatValueModifier::Type::MULTI_MUL:
					multiplicative_multiplier *= (1 + modifier->get_value());
					break;

				default:
					break;
			};
		}

		// current formula
		current = (base + flat_modifier) * additive_multiplier * multiplicative_multiplier;
	}

	void _on_modifier_expire(const Ref<FloatValueModifier>& modifier) {
		List<Ref<FloatValueModifier>>::Element *e = modifiers.find(modifier);
		if (e) {
			Ref<FloatValueModifier> mod = e->get();
			mod->disconnect("on_expire", callable_mp(this, &FloatAttribute::_on_modifier_expire));
			e->erase();
			_recalculate();
		}
	}

	void remove_modifier(Ref<FloatValueModifier> modifier) {
		_on_modifier_expire(modifier);
	}

	// current cannot be set - is recalculated whenever attribute is changed
	virtual float get_current() {
		return current;
	}

	/**
	 * Applies modifier causing modification to 
	*/
	void add_modifier(Ref<FloatValueModifier> modifier) {
		modifiers.push_back(modifier);
		modifier->connect("on_expire", callable_mp(this, &FloatAttribute::_on_modifier_expire));
		_recalculate();
	}

	void set_base(float new_base);
	float get_base();

    FloatAttribute();
	FloatAttribute(float p_base);
};

/**
 * FloatAttribute, which current value is clamped between min and max
*/
class CappedFloatAttribute : public FloatAttribute {
GDCLASS(CappedFloatAttribute, FloatAttribute);
protected:
	float min = 0.0f;
	float max = 100.0f;

	static void _bind_methods();
public:
	void set_min(float p_min);
	float get_min();
	void set_max(float p_max);
	float get_max();
	/**
	 * @return current attribute value, clamped between min and max
	*/
	float get_current() override;
	float get_current_uncapped();

	CappedFloatAttribute(){};
	CappedFloatAttribute(float p_current, float p_min, float p_max);
};

class CappedResourceAttribute : public CappedFloatAttribute {
GDCLASS(CappedResourceAttribute, CappedFloatAttribute);
protected:
	static void _bind_methods();
	void _notification(int p_notification);
public:
	void set_current(float p_current) {
		float old = current;
		current = p_current;
		emit_signal("current_value_changed", old, current);
	};

	CappedResourceAttribute(){};
	CappedResourceAttribute(float p_current, float p_min, float p_max) : CappedFloatAttribute(p_current, p_min, p_max){}
};
#endif // FLOAT_ATTRIBUTE_INCLUDED
