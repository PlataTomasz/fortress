#include "example_implementor.h"
#include <shared/entities/traits/traits.h>

void ExampleImplementor::_bind_methods() {
    ADD_SIGNAL(MethodInfo("interface_signal", PropertyInfo(Variant::OBJECT, "example_interface")));

    ::ClassDB::bind_method(D_METHOD("example_interface_method"), method_pointer_fix<ExampleImplementor>(&ExampleImplementor::example_interface_method));
}

void ExampleImplementor::example_interface_method() {
    print_line("Example interface implementation in ExampleImplementor!");
    emit_signal("interface_signal", this);
}