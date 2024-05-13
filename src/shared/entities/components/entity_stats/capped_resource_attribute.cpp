#include "float_attribute.h"

void CappedResourceAttribute::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("set_current"), &CappedResourceAttribute::set_current);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "current"), "set_current", "get_current");
}

void CappedResourceAttribute::_notification(int p_notification) {
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        {
            current = max;
        }
        break;
    
    default:
        break;
    }
}