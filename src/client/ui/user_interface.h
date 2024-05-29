#if !defined(USER_INTERFACE_INCLUDED)
#define USER_INTERFACE_INCLUDED

#include <scene/gui/control.h>

class CharacterSelectionUI;

class MainMenu;

class UserInterface : public Control {
GDCLASS(UserInterface, Control);
private:
    MainMenu *main_menu = nullptr;
protected:
    void _ready();

    void _notification(int p_notification);

    static void _bind_methods();
public:
    MainMenu *get_main_menu();
    void set_main_menu(MainMenu *p_main_menu);
};

#endif // USER_INTERFACE_INCLUDED
