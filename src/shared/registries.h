#if !defined(REGISTRIES_H_INCLUDED)
#define REGISTRIES_H_INCLUDED

#include <core/string/string_name.h>
#include <core/templates/hash_map.h>

class Mercenary;
class Ability;

template<class T>
class Registry
{
private:
    HashMap<StringName, T> data;

public:
    /**
     * @warning This method doesn't check if key already exists
    */
    void register_item(StringName name, T obj)
    {
        data[name] = obj;
    }

    /**
     * @return Copy of object stored under that name, null otherwise
    */
    T get_item(StringName name)
    {
        if(data.has(name))
        {
            return data.get(name);
        }
        else
        {
            return NULL;
        }
    }

    Registry()
    {

    }

    ~Registry()
    {

    }
};

class Registries
{
private:
    Registries(){}
public:
    static Registries* singleton;

    static Registries *get_singleton()
    {
        if(!singleton)
        {
            singleton = new Registries();
        }
        return singleton;
    }

public:
    Registry<Mercenary*> MERCENARIES;
    Registry<Ability*> ABILITIES;
};

Registries *Registries::singleton = nullptr;

#endif // REGISTRIES_H_INCLUDED
