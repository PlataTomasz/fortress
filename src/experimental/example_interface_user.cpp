#include "example_interface_user.h"

#include <core/variant/variant.h>

void ExampleInterfaceUser::_bind_methods() {
    ::ClassDB::bind_method(D_METHOD("connect_test_signal"), &ExampleInterfaceUser::connect_test_signal);

    // Binding method with interface causes compilation error
    //::ClassDB::bind_method(D_METHOD("_on_interface_signal_received"), &ExampleInterfaceUser::_on_interface_signal_received);
}

void ExampleInterfaceUser::connect_test_signal(Object *obj) {
    obj->connect("interface_signal", callable_mp(this, &ExampleInterfaceUser::_on_interface_signal_received));
}