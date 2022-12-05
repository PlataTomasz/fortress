#if !defined(GAME_MAP_HPP)
#define GAME_MAP_HPP

#include <scene/3d/node_3d.h>

class EntityManager : public Node3D
{
public:
    EntityManager()
    {

    };
};

class GameMap : public Node3D
{
private:
    EntityManager *entityManagerInstance = nullptr;
public:
    //Getters/Setters

    GameMap()
    {
        entityManagerInstance = (EntityManager*)get_node(NodePath("Entities"));

        if(entityManagerInstance == nullptr)
        {
            entityManagerInstance = new EntityManager();
        }

        this->add_child((Node*)entityManagerInstance);
    }

    ~GameMap()
    {

    }
};

#endif // GAME_MAP_HPP
