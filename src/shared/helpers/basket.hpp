#if !defined(BASKET_HPP_INCLUDED)
#define BASKET_HPP_INCLUDED

class Node;

/**
 * Basket is a class designed to act as smart pointer for Nodes, which are part of SceneTree.
 * @note That class does NOT do any cleanup! It leaves that responsibility to engine.
*/
class Basket
{
//Compile time check
//static_assert(std::is_base_of<Node, T>::value, "T must inherit from list");

private:
    Node* node = nullptr;

    Callable node_exit_callable;

    /**
     * Cleanup method, which is called when Node is leaving scene tree
    */
    void on_node_exit_scene();

public:
    /**
     * @return true if pointer to Node is still valid, false otherwise
    */
    bool is_valid();

    /**
     * @returns Node pointer stored by that object, nullptr if invalid
     * 
    */
    Node* get();

    void reset(Node* new_ptr);

    //Operator overloads
    /**
     * @returns Reference to object stored in pointer
    */
    Node& operator*() const;

    /**
     * 
    */
    bool operator==(const Basket& other);
    bool operator==(Node* other);

    Basket& operator=(Node* rhs);
    Basket& operator=(Basket& rhs);

    //Constructors
    Basket(Node* node);
    Basket(const NodePath& node_path);
    //Move
    Basket(Basket&& basket);
    //Copy
    Basket(Basket& basket);

    ~Basket(){};
};

#endif // BASKET_HPP_INCLUDED
