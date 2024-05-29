#if !defined(CHARACTER_SELECT_ELEM_INCLUDED)
#define CHARACTER_SELECT_ELEM_INCLUDED

#include <scene/gui/split_container.h>

#include <core/object/ref_counted.h>
#include <scene/resources/texture.h>

class TextureButton;

class CharacterSelectElem : public VSplitContainer {
GDCLASS(CharacterSelectElem, VSplitContainer);
private:
    Label *name_label = nullptr;
    TextureButton *texture_button = nullptr;

    String mercenary_identifier;

    void _notification(int p_notification);
    void _init();
    void _draw();
protected:
    virtual void unhandled_input(const Ref<InputEvent> &p_event);
    static void _bind_methods();
public:
    void set_icon(const Ref<Texture2D>& p_icon);
    void set_displayed_name(const String& p_name);

    Label *get_name_label();
    void set_name_label(Label *p_name_label);
    TextureButton *get_texture_button();
    void set_texture_button(TextureButton *p_texture_button);

    String get_mercenary_identifier();
    void set_mercenary_identifier(const String& p_identifier);
};

#endif // CHARACTER_SELECT_ELEM_INCLUDED
