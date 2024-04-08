#if !defined(GAMEPLAY_ATTRIBUTES_INCLUDED)
#define GAMEPLAY_ATTRIBUTES_INCLUDED

#include <core/templates/hash_map.h>
#include <core/templates/oa_hash_map.h>
#include <core/variant/typed_array.h>

#include <core/string/ustring.h>

class GameplayAttributes : public Resource {
    /*
        Valid attribute value types are:
        - String
        - Int
        - Float
        - Array of single valid type
    */
    // HashMap<String, Variant> attribute_map;
    Dictionary attribute_map;
public:
    // Supported type getters
    bool get_bool_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        bool attribute_value =  attribute_variant.get_type() == Variant::BOOL ? bool(attribute_variant) : false;
        return attribute_value;
    };

    int get_int_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        int attribute_value =  attribute_variant.get_type() == Variant::INT ? int(attribute_variant) : 0;
        return attribute_value;
    };

    float get_float_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        float attribute_value = attribute_variant.get_type() == Variant::FLOAT ? float(attribute_variant) : 0;
        return attribute_value;
    }

    String get_string_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        String attribute_value = attribute_variant.get_type() == Variant::STRING ? String(attribute_variant) : "";
        return attribute_value;
    };

    PackedInt32Array get_int32_array_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        PackedInt32Array attribute_value = attribute_variant.get_type() == Variant::PACKED_INT32_ARRAY ? PackedInt32Array(attribute_variant) : PackedInt32Array() ;
        return attribute_value;
    }

    PackedInt64Array get_int64_array_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        PackedInt64Array attribute_value = attribute_variant.get_type() == Variant::PACKED_INT64_ARRAY ? PackedInt64Array(attribute_variant) : PackedInt64Array() ;
        return attribute_value;
    }

    PackedFloat32Array get_float32_array_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        PackedFloat32Array attribute_value = attribute_variant.get_type() == Variant::PACKED_FLOAT32_ARRAY ? PackedFloat32Array(attribute_variant) : PackedFloat32Array() ;
        return attribute_value;
    }

    PackedFloat64Array get_float64_array_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        PackedFloat64Array attribute_value = attribute_variant.get_type() == Variant::PACKED_FLOAT64_ARRAY ? PackedFloat64Array(attribute_variant) : PackedFloat64Array() ;
        return attribute_value;
    }

    PackedStringArray get_string_array_attribute(const String &name) {
        Variant attribute_variant = get_attribute(name);
        PackedStringArray attribute_value = attribute_variant.get_type() == Variant::PACKED_STRING_ARRAY ? PackedStringArray(attribute_variant) : PackedStringArray() ;
        return attribute_value;
    }

    // Returns variant of supported type
    Variant get_attribute(const String &name) {
        if ( attribute_map.has(name) ) {
            return attribute_map.get_valid(name);
        } else {
            return Variant();
        }
    };

    void set_attribute(const String &name, Variant value) {
        // Check if Variant is of supported type, else ignore
        switch ( value.get_type() )
        {
        case Variant::INT:
        case Variant::FLOAT:
        case Variant::STRING:
        case Variant::PACKED_INT32_ARRAY:// Array types
        case Variant::PACKED_INT64_ARRAY:
        case Variant::PACKED_FLOAT32_ARRAY:
        case Variant::PACKED_FLOAT64_ARRAY:
        case Variant::PACKED_STRING_ARRAY:
            // Supported type - go ahead
            attribute_map[name] = value;
            break;
        default:
            ERR_FAIL_MSG("Passed Variant is not supported GameplayAttribute value. Value was not added.");
            break;
        }
    };

    operator Dictionary() {
        return attribute_map;
    }
};

#endif // GAMEPLAY_ATTRIBUTES_INCLUDED