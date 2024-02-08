#if !defined(COMPONENT_METHODS_INCLUDED)
#define COMPONENT_METHODS_INCLUDED

#include <scene/main/node.h>
#include <shared/helpers/object_ptr.h>

namespace Components
{
    //Finds first component of matching type and returns it; Returns empty ObjectPtr if component doesn't exists on entity
    //Current implementation uses dynamic_cast, therefore doesn't support GDScript classes. In the future, probably property based implementation will be used.
    template<class T>
    static ObjectPtr<T> get_component(Node *node, StringName component_type)
    {
        TypedArray<Node> children = node->get_children();
        for(int i = 0;i < children.size();i++)
        {
            if(T *cast_result = Object::cast_to<>(children[i].operator Object *()))
            {
                return cast_result;
            }
        }
        return nullptr;
    };

}

#endif // COMPONENT_METHODS_INCLUDED
