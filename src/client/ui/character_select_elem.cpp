#include "character_select_elem.h"

void CharacterSelectElem::_notification(int p_notification) {
    switch (p_notification)
    {
    case NOTIFICATION_POSTINITIALIZE:
        _init();
        break;

    case NOTIFICATION_DRAW:
        _draw();
        break;
    
    default:
        break;
    }
}

void CharacterSelectElem::_init() {
    
}

void CharacterSelectElem::_draw() {
    
}

void CharacterSelectElem::unhandled_input(const Ref<InputEvent> &p_event) {
	if (InputEventMouseButton *mouse_btn_event = Object::cast_to<InputEventMouseButton>(p_event.ptr())) {
		if (mouse_btn_event->is_pressed() && mouse_btn_event->get_button_index() == MouseButton::LEFT) {
            grab_focus();
		}
	}
}