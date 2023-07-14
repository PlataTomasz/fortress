#if !defined(ObjectPtr_HPP_INCLUDED)
#define ObjectPtr_HPP_INCLUDED

#include <type_traits>

#include <core/variant/callable.h>
#include <core/object/class_db.h>
#include <core/object/object.h>
#include <scene/scene_string_names.h>
#include <scene/main/window.h>
#include <core/object/object_id.h>

class NodePath;

/**
 * ObjectPtr is a class designed to act as smart pointer for Objects, which are part of SceneTree.
 * @note That class does NOT do any cleanup! It leaves that responsibility to engine.
*/
template<class T>
class ObjectPtr
{
static_assert(std::is_base_of_v<Object, T> == true);

private:
    ObjectID objId;
    T *obj = nullptr;
public:
    /**
     * @return true if pointer to Object is still valid, false otherwise
    */
    bool is_valid() const
    {
        //Query ObjectDB for validity of contained Object
        return bool(obj != nullptr && obj == ObjectDB::get_instance(objId));
    }

    /**
     * @return true if contained object is not nullptr
    */
    bool is_set()
    {
        return obj != nullptr;
    }

    /**
     * @returns Object pointer stored by that object if set
     * @returns nullptr if unset
     * @warning Might return invalid pointer - Use get_valid() if you care about validity()
    */
    T *get()
    {
        return obj;
    }

    /**
     * @returns Object pointer stored by that object if valid
     */
    T *get_valid()
    {
        if(is_valid())
            return obj;
        else
            return nullptr;
    }

    void reset(T *new_ptr)
    {
        ERR_FAIL_COND_MSG(!new_ptr || !ObjectDB::get_instance(new_ptr->get_instance_id()), "ObjectPtr creation error - Passed Object is already invalid!");
        this->obj = new_ptr;
        this->objId = new_ptr->get_instance_id();
    }

    //Operator overloads
    /**
     * @returns Reference to object stored in pointer
    */
    T& operator *() const
    {
        return *obj;
    }
    
    bool operator==(const ObjectPtr& other)
    {
        return is_valid() && obj == other.obj;
    }

    operator bool() const
    {
        return this->is_valid();
    }

    ObjectPtr& operator=(ObjectPtr& other)
    {
        this->reset(other.get());
    }

    ObjectPtr& operator=(T* rhs)
    {
        reset(rhs);
        return *this;
    }

    //ObjectPtr& operator=(ObjectPtr& rhs);

    T* operator->()
    {
        return static_cast<T*>(this->obj);
    }

    operator Variant()
    {
        //Make sure variant will store valid object - If not, empty variant
        if(Object *object = get())
        {
            return Variant(object);
        }
        else
        {
            return Variant();
        }
    }

    //Constructors
    ObjectPtr(const NodePath& node_path)
    {
        Node* window = static_cast<Node*>(SceneTree::get_singleton()->get_root());
        //Checking if such path is valid
        ERR_FAIL_NULL_MSG(window, "ObjectPtr creation error - Scene tree root is invalid!");
        //Dynamic cast beacuse we don't know type of - Maybe use get_class_name() instead?
        Object *obj = Object::cast_to<Object*>(window->get_node(node_path));
        ERR_FAIL_NULL_MSG(obj, "ObjectPtr creation error - Object path is invalid or node doesn't extend template type!");
        
        this->obj = obj;
        this->objId = obj->get_instance_id();
    }


    ObjectPtr() {};

    //Move
    ObjectPtr(ObjectPtr&& objectPtr)
    {
        //TODO: How does move constructor work?
        this->reset(objectPtr.obj);
    }

    //Copy
    //NOTE: Unused, might have issues with template reference argument
    ObjectPtr(ObjectPtr& objectPtr)
    {
        reset(objectPtr.obj);
    }

    ObjectPtr(T *obj)
    {
        reset(obj);
    }
};

#endif // ObjectPtr_HPP_INCLUDED
