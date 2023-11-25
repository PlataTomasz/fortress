#include "component.h"

void Component::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_ENTER_TREE:
    {
        print_line(get_name(), "has been added to the scene!");
        get_parent()->connect("child_order_changed", callable_mp(this, &Component::_on_sibling_order_changed));
    }
    break;

    case NOTIFICATION_PARENTED:
    {
        _on_parent_changed();
    }
    break;

    default:
        break;
    }
}

void Component::_on_sibling_added(Node *sibling)
{
    
}

void Component::_on_sibling_removed(Node *sibling)
{
    
}

void Component::_on_parent_changed()
{

}

void Component::_on_child_added(Node *child)
{

}

void Component::_on_child_removed(Node *child)
{
    
}