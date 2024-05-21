#if !defined(EXAMPLE_INTERFACE_USER_INCLUDED)
#define EXAMPLE_INTERFACE_USER_INCLUDED

#include <core/object/object.h>
#include <core/object/class_db.h>

#include <experimental/i_example.h>

class ExampleInterfaceUser : public Object {
GDCLASS(ExampleInterfaceUser, Object);
private:
    void _on_interface_signal_received(IExample *p_example) {
        print_line("_on_interface_signal_received");
    };
    void connect_test_signal(Object *obj);
protected:
    static void _bind_methods();
};

#endif // EXAMPLE_INTERFACE_USER_INCLUDED
