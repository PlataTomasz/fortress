#if !defined(EXAMPLE_INTERFACE_INCLUDED)
#define EXAMPLE_INTERFACE_INCLUDED

#include <core/variant/variant.h>

class Interface {
public:

};

class IExample : public Interface {
public:
    virtual void example_interface_method() = 0;
};

template<>
struct GetTypeInfo<IExample *> {
	static const Variant::Type VARIANT_TYPE = Variant::OBJECT;
	static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::OBJECT, String(), PROPERTY_HINT_NONE, "Interface");
	}
};

template <>
struct VariantCaster<IExample *> {
	static _FORCE_INLINE_ IExample * cast(const Variant &p_variant) {
		return (IExample *)(p_variant.operator Object *());
	}
};


#endif // EXAMPLE_INTERFACE_INCLUDED
