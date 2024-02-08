#include "component.h"

void Component::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_ENTER_TREE:
    {
        print_line(get_name(), "has been added to the scene!");
        get_parent()->connect("child_entered_tree", callable_mp(this, &Component::_on_sibling_added));
        get_parent()->connect("child_exiting_tree", callable_mp(this, &Component::_on_sibling_removed));
        connect("child_entered_tree", callable_mp(this, &Component::_on_child_added));
        connect("child_exiting_tree", callable_mp(this, &Component::_on_child_removed));
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
//Currently unused - assume that parent NEVER changes
void Component::_on_parent_changed()
{

}

void Component::_on_child_added(Node *child)
{

}

void Component::_on_child_removed(Node *child)
{
    
}

Component::Component()
{
    
}