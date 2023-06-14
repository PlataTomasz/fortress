#include "basket.hpp"
#include <scene/main/node.h>
#include <scene/scene_string_names.h>
#include <scene/main/window.h>

#include <core/string/node_path.h>

//NOTE: Currently uses tree_exit signal, which means that technically Object "might" be still valid
void Basket::invalidate_handler()
{
    this->node = nullptr;
}

bool Basket::is_valid()
{
    return node != nullptr;
}

Object* Basket::get()
{
    return node;
}

void Basket::reset(Object* new_ptr)
{
    if(this->node != nullptr)
    {
        this->node->disconnect_notification(Object::NOTIFICATION_PREDELETE, invalidate_handler_callable);
        this->node = nullptr;
    }

    ERR_FAIL_NULL_MSG(new_ptr, "Basket creation error - Passed Object is already invalid!");
    this->node = new_ptr;
    this->node->connect_notification(Object::NOTIFICATION_PREDELETE, invalidate_handler_callable);
}

Object& Basket::operator*() const {
    return *node;
}

bool Basket::operator==(const Basket& other)
{
    return this->node == other.node;
}

bool Basket::operator==(Object* other)
{
    return this->node == other;
}

Basket& Basket::operator=(Object* rhs)
{
    reset(rhs);
    return *this;
}

Basket& Basket::operator=(Basket& rhs)
{
    //Copy constructor
    Basket basket = Basket(rhs);
    return basket;
}

Basket::Basket(Object* node) : invalidate_handler_callable(callable_mp(this, &Basket::invalidate_handler))
{
    reset(node);
};

Basket::Basket(const NodePath& node_path) : invalidate_handler_callable(callable_mp(this, &Basket::invalidate_handler))
{
    Node* window = static_cast<Node*>(SceneTree::get_singleton()->get_root());

    //Checking if such path is valid
    ERR_FAIL_NULL_MSG(window, "Basket creation error - Scene tree root is invalid!");
    Object* node = static_cast<Object*>(window->get_node(node_path));

    ERR_FAIL_NULL_MSG(node, "Basket creation error - Object path is invalid!");
    this->node = node;
    this->node->connect(SceneStringNames::get_singleton()->tree_exiting, callable_mp(this, &Basket::invalidate_handler));;
}

Basket::Basket(Basket&& basket)
{
    //TODO: How does move constructor work?
    this->invalidate_handler_callable = basket.invalidate_handler_callable;
    this->reset(basket.node);
}

Basket::Basket(Basket& basket) : invalidate_handler_callable(callable_mp(this, &Basket::invalidate_handler))
{
    reset(basket.node);
}