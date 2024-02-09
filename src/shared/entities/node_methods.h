#if !defined(NODE_METHODS_INCLUDED)
#define NODE_METHODS_INCLUDED

template<class T>
class ObjectPtr;

class Component;

namespace EntityGlobals
{
    template<class T>
    T *get_component(Node *entity, StringName component_name);
};

#endif // NODE_METHODS_INCLUDED
