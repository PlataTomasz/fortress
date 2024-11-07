#if !defined(MAIN_MENU_INCLUDED)
#define MAIN_MENU_INCLUDED

#include <scene/gui/control.h>
#include <scene/gui/center_container.h>
#include <scene/gui/panel_container.h>
#include <scene/gui/button.h>

class LineEdit;

// Class encapsulating behaviour for a GUI, which is displayed when a client is started
class MainMenu : public PanelContainer {
GDCLASS(MainMenu, PanelContainer);
private:
    LineEdit *ip_input = nullptr;
    LineEdit *nickname_input = nullptr;
    BaseButton *join_button = nullptr;

    Control *character_select_area = nullptr;

    Ref<ButtonGroup> character_button_group;
protected:
    static void _bind_methods();
    void _notification(int p_notification);
public:
    String get_choosen_nickname();
    String get_server_adress();
    int get_server_port();
    String get_selected_mercenary();

    LineEdit *get_nickname_input();
    void set_nickname_input(LineEdit *p_nickname_input);
    LineEdit *get_ip_input();
    void set_ip_input(LineEdit *p_ip_input);
    BaseButton *get_join_button();
    void set_join_button(BaseButton *p_join_button);
    Control *get_character_select_area();
    void set_character_select_area(Control *p_character_select_area);

    Ref<ButtonGroup> get_character_button_group();
    void set_character_button_group(const Ref<ButtonGroup> &p_button_group);
};

#endif // MAIN_MENU_INCLUDED
