#if !defined(BASKET_HPP_INCLUDED)
#define BASKET_HPP_INCLUDED

#include <core/variant/callable.h>
#include <core/object/class_db.h>
#include <core/object/object.h>

class NodePath;

/**
 * Basket is a class designed to act as smart pointer for Objects, which are part of SceneTree.
 * @note That class does NOT do any cleanup! It leaves that responsibility to engine.
*/
class Basket : public Object
{
//Compile time check
//static_assert(std::is_base_of<Object, T>::value, "T must inherit from list");
GDCLASS(Basket, Object);
private:
    Object* node = nullptr;

    Callable invalidate_handler_callable;

    void invalidate_handler();
public:
    /**
     * @return true if pointer to Object is still valid, false otherwise
    */
    bool is_valid();

    /**
     * @returns Object pointer stored by that object, nullptr if invalid
     * 
    */
    Object* get();

    void reset(Object* new_ptr);

    //Operator overloads
    /**
     * @returns Reference to object stored in pointer
    */
    Object& operator*() const;

    /**
     * 
    */
    bool operator==(const Basket& other);
    bool operator==(Object* other);

    Basket& operator=(Object* rhs);
    Basket& operator=(Basket& rhs);

    //Constructors
    Basket(Object* node);
    Basket(const NodePath& node_path);
    //Move
    Basket(Basket&& basket);
    //Copy
    Basket(Basket& basket);

    ~Basket(){};
};

#endif // BASKET_HPP_INCLUDED
