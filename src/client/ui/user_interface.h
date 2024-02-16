#if !defined(USER_INTERFACE_INCLUDED)
#define USER_INTERFACE_INCLUDED

#include <scene/gui/control.h>

class UserInterface : public Control {
GDCLASS(UserInterface, Control);
private:
    Control *character_selection = nullptr;
protected:
    void _init();

    void _notification(int p_notification);
};

#endif // USER_INTERFACE_INCLUDED
