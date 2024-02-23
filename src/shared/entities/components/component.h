#if !defined(COMPONENT_INCLUDED)
#define COMPONENT_INCLUDED

#include <scene/main/node.h>

/**
 * Base class for all components
 * TODO: Display proper warning on missing pointers via _get_configuration_warnings
*/
class Component : public Node
{
GDCLASS(Component, Node);
private:

protected:
    void _notification(int p_notification);

    void _on_sibling_added(Node *sibling);
    void _on_sibling_removed(Node *sibling);

    virtual void _on_sibling_added_impl(Node *sibling);
    virtual void _on_sibling_removed_impl(Node *sibling);
public:
    Component();
};

#endif // COMPONENT_INCLUDED
