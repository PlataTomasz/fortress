#if !defined(COMPONENT_STRINGNAMES_INCLUDED)
#define COMPONENT_STRINGNAMES_INCLUDED

#include <core/string/string_name.h>

class ComponentStringNames
{
private:
    static ComponentStringNames* singleton;

    ComponentStringNames();
protected:
public:
    static ComponentStringNames* get_singleton()
    {
        if(!singleton)
        {
            singleton = memnew(ComponentStringNames);
        }
        return singleton;
    }

    StringName attribute_component;
    StringName status_effect_component;
    StringName damageable_component;
    StringName movement_component;
};

#endif // COMPONENT_STRINGNAMES_INCLUDED
