#if !defined(CHARACTER_SELECT_ELEM_INCLUDED)
#define CHARACTER_SELECT_ELEM_INCLUDED

#include <scene/gui/split_container.h>

class CharacterSelectElem : public VSplitContainer {
GDCLASS(CharacterSelectElem, VSplitContainer);
private:
    void _notification(int p_notification);
    void _init();
    void _draw();
protected:
    virtual void unhandled_input(const Ref<InputEvent> &p_event);
};

#endif // CHARACTER_SELECT_ELEM_INCLUDED
