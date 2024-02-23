#include "component.h"

void Component::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_ENTER_TREE:
    {
        get_parent()->connect("child_entered_tree", callable_mp(this, &Component::_on_sibling_added));
        get_parent()->connect("child_exiting_tree", callable_mp(this, &Component::_on_sibling_removed));

    }
    break;

    case NOTIFICATION_EXIT_TREE:
    {
        get_parent()->disconnect("child_entered_tree", callable_mp(this, &Component::_on_sibling_added));
        get_parent()->disconnect("child_exiting_tree", callable_mp(this, &Component::_on_sibling_removed));
    }
    break;

    default:
        break;
    }
}

void Component::_on_sibling_added(Node *sibling)
{
    _on_sibling_added_impl(sibling);
}

void Component::_on_sibling_removed(Node *sibling)
{
    _on_sibling_added_impl(sibling);
}

void Component::_on_sibling_added_impl(Node *sibling) {

}

void Component::_on_sibling_removed_impl(Node *sibling) {

}

Component::Component()
{
    
}