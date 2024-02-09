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

    StringName ATTRIBUTES;
    StringName STATUS_EFFECT_VICTIM;
    StringName DAMAGEABLE;
};

#endif // COMPONENT_STRINGNAMES_INCLUDED
