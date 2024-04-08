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
	};
private:
	float value = 0;
	Type type = FLAT_ADD;
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
		emit_signal("expired", this);
	};
};

// Numerical attribute
class FloatAttribute : public Attribute {
GDCLASS(FloatAttribute, Attribute);
private:
	float base = 0;
	List<Ref<FloatValueModifier>> modifiers;
	float total = 0;
public:

	// Recalculates total value - Mostly called when a modifier has expired
	void _recalculate() {
		// Recalculate total - might be different now
		float flat_modifier = 0;
		float additive_multiplier = 1;
		float multiplicative_multiplier = 1;

		for(Ref<FloatValueModifier> modifier : modifiers) {
			switch (modifier->get_type())
			{
			case FloatValueModifier::Type::FLAT_ADD:
				flat_modifier+=modifier->get_value();
				break;
			
			case FloatValueModifier::Type::MULTI_ADD:
				additive_multiplier+=modifier->get_value();
				break;

			case FloatValueModifier::Type::MULTI_MUL:
				multiplicative_multiplier*=(1+modifier->get_value());
				break;

			default:
				break;
			};
		}

		// Total formula
		total = (base + flat_modifier) * additive_multiplier * multiplicative_multiplier;
	}

	void _on_modifier_expire(Ref<FloatValueModifier>& modifier) {
		List<Ref<FloatValueModifier>>::Element *e = modifiers.find(modifier);
		if (e) {
			e->erase();
			_recalculate();
		}
	}

	// Total cannot be set - is recalculated whenever attribute is changed
	float get_total() {
		return total;
	}

	void add_modifier(Ref<FloatValueModifier> modifier) {
		//modifier->connect("expire", callable_mp(this, &FloatAttribute::_on_modifier_expire));
	}

    FloatAttribute();
};

#endif // FLOAT_ATTRIBUTE_INCLUDED
