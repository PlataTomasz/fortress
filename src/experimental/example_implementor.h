#if !defined(EXAMPLE_IMPLEMENTOR_INCLUDED)
#define EXAMPLE_IMPLEMENTOR_INCLUDED

#include <core/object/object.h>
#include <core/object/class_db.h>

#include "i_example.h"

/**
 * Problem: None(?)
 */
class ExampleImplementor : public Object, public IExample {
GDCLASS(ExampleImplementor, Object);
    void example_interface_method() override;
protected:
    static void _bind_methods();
};

#endif // EXAMPLE_IMPLEMENTOR_INCLUDED
