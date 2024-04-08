#if !defined(ATTRIBUTE_MODIFIER_INCLUDED)
#define ATTRIBUTE_MODIFIER_INCLUDED

#include <scene/main/node.h>
#include <shared/core/systems/gameplay/gameplay_attributes.h>


// SET Attribute modifier priority should be determined wheter modifier is for enemy or ally unit
class AttributeModifier {
private:
    enum ModifierType {
        SET = 1,
        ADD,
        SUB,
        MUL,
        DIV,
        CUSTOM
    };

    // Custom functions to apply status effect and revert applicance
    float get_apply_modifier_custom() {};
    float get_revert_modifier_custom() {};

    String attribute_name;
    // If type is CUSTOM, then custom methods are used
    AttributeModifier::ModifierType type;
    float value;

public:


    AttributeModifier(){};
};

#endif // ATTRIBUTE_MODIFIER_INCLUDED
