#include "float_attribute.h"

void CappedResourceAttribute::_bind_methods() {

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