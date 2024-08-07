#if !defined(CHARACTER_SELECT_ELEM_INCLUDED)
#define CHARACTER_SELECT_ELEM_INCLUDED

#include <scene/gui/split_container.h>

#include <core/object/ref_counted.h>
#include <scene/resources/texture.h>

class TextureButton;
class TextureRect;

class CharacterSelectElem : public VSplitContainer {
GDCLASS(CharacterSelectElem, VSplitContainer);
private:
    Label *name_label = nullptr;
    String title = "empty";
    String character_index;

    Ref<Texture2D> icon;

    TextureButton *texture_button = nullptr;
    TextureRect *mercenary_icon_quad = nullptr;

    void _notification(int p_notification);
    void _init();
    void _draw();
protected:
    virtual void unhandled_input(const Ref<InputEvent> &p_event);
    static void _bind_methods();
public:
    void set_mercenary_icon_quad(TextureRect *new_mercenary_icon_quad);
    TextureRect *get_mercenary_icon_quad();

    void set_title(const String& new_title);
    String get_title();

    void set_character_index(const String& new_character_index);
    String get_character_index();

    void set_icon(const Ref<Texture2D>& p_icon);
    Ref<Texture2D> get_icon();
    void set_displayed_name(const String& p_name);

    Label *get_name_label();
    void set_name_label(Label *p_name_label);
    TextureButton *get_texture_button();
    void set_texture_button(TextureButton *p_texture_button);
};

#endif // CHARACTER_SELECT_ELEM_INCLUDED
