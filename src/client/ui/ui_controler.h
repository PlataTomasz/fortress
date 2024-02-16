#if !defined(UI_CONTROLLER_INCLUDED)
#define UI_CONTROLLER_INCLUDED

#include <scene/main/node.h>

//UI is the last thing loaded
class UIController : public Node {
private:
    void _enter_tree();
    void _ready();
    void _on_new_entity_entered(Node *node);
    void _on_entity_leave(Node *node);
protected:
    void _notification(int p_notification);
public:
    
};

#endif // UI_CONTROLLER_INCLUDED
