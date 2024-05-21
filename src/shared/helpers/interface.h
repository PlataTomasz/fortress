#if !defined(INTERFACE_INCLUDED)
#define INTERFACE_INCLUDED

#include <core/object/object.h>
#include <core/object/class_db.h>

// Use this macro Outside Interface definition to setup new interface
// NOTE: Currently doesn't work in GDSCRIPT. It only exists to seamlessly use signals.
#define SETUP_INTERFACE(m_name)                                                             \
template<>                                                                                  \
struct GetTypeInfo<m_name *> {                                                              \
	static const Variant::Type VARIANT_TYPE = Variant::OBJECT;                              \
	static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;           \
	static inline PropertyInfo get_class_info() {                                           \
		return PropertyInfo(Variant::OBJECT, String(), PROPERTY_HINT_NONE, "Interface");    \
	}                                                                                       \
};                                                                                          \
template <>                                                                                 \
struct VariantCaster<m_name *> {                                                            \  
	static _FORCE_INLINE_ m_name * cast(const Variant &p_variant) {                         \
		return (m_name *)(p_variant.operator Object *());                                   \
	}                                                                                       \
};

#endif // INTERFACE_INCLUDED
