#include "basket.hpp"
#include <scene/main/node.h>
#include <scene/scene_string_names.h>
#include <scene/main/window.h>

//NOTE: Currently uses tree_exit signal, which means that technically Node "might" be still valid
void Basket::on_node_exit_scene()
{
    this->node = nullptr;
}

bool Basket::is_valid()
{
    return node != nullptr;
}

Node* Basket::get()
{
    return node;
}

void Basket::reset(Node* new_ptr)
{
    if(this->node != nullptr)
    {
        this->node->disconnect(SceneStringNames::get_singleton()->tree_exiting, node_exit_callable);
    }
    else
    {
        ERR_FAIL_NULL_MSG(new_ptr, "Basket creation error - Passed Node is already invalid!");
        this->node = new_ptr;
        this->node->connect(SceneStringNames::get_singleton()->tree_exiting, node_exit_callable);
    }
}

Node& Basket::operator*() const {
    return *node;
}

bool Basket::operator==(const Basket& other)
{
    return this->node == other.node;
}

bool Basket::operator==(Node* other)
{
    return this->node == other;
}

Basket& Basket::operator=(Node* rhs)
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

Basket::Basket(Node* node) : node_exit_callable(callable_mp(this, &Basket::on_node_exit_scene))
{
    reset(node);
};

Basket::Basket(const NodePath& node_path) : node_exit_callable(callable_mp(this, &Basket::on_node_exit_scene))
{
    Node* window = static_cast<Node*>(SceneTree::get_singleton()->get_root());

    //Checking if such path is valid
    ERR_FAIL_NULL_MSG(window, "Basket creation error - Scene tree root is invalid!");
    Node* node = window->get_node(node_path);

    ERR_FAIL_NULL_MSG(node, "Basket creation error - Node path is invalid!");
    this->node = node;
    this->node->connect(SceneStringNames::get_singleton()->tree_exiting, callable_mp(this, &Basket::on_node_exit_scene));;
}

Basket::Basket(Basket&& basket)
{
    //TODO: How does move constructor work?
    this->node_exit_callable = basket.node_exit_callable;
    this->reset(basket.node);
}

Basket::Basket(Basket& basket) : node_exit_callable(callable_mp(this, &Basket::on_node_exit_scene))
{
    reset(basket.node);
}