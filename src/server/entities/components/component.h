#if !defined(COMPONENT_INCLUDED)
#define COMPONENT_INCLUDED

#include <scene/main/node.h>

/**
 * Base class for all components
 * TODO: Display proper warning on missing pointers via _get_configuration_warnings
*/
class Component : public Node
{
private:
    
protected:
    void _notification(int p_notification);

    virtual void _on_sibling_added(Node *sibling);
    virtual void _on_sibling_removed(Node *sibling);
    virtual void _on_parent_changed();
    virtual void _on_child_added(Node *child);
    virtual void _on_child_removed(Node *child);
public:
    Component();
};

#endif // COMPONENT_INCLUDED
