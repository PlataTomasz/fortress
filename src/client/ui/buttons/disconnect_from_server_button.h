#if !defined(DISCONNECT_FROM_SERVER_BUTTON_INCLUDED)
#define DISCONNECT_FROM_SERVER_BUTTON_INCLUDED

#include <scene/gui/button.h>

class DisconnectFromServerButton : public Button {
GDCLASS(DisconnectFromServerButton, Button);
private:
    void _on_click();
    void _init();
protected:
    void _notification(int p_notification);
public:
};

#endif // DISCONNECT_FROM_SERVER_BUTTON_INCLUDED
