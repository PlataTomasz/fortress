#if !defined(ENTITY_MANAGER_HPP_INCLUDED)
#define ENTITY_MANAGER_HPP_INCLUDED

/*
Entity API:
 - What is Entity: Currently we think of Entity as a Node3D, which represents any thing that can move and interact with GameMap
 - What is needed?(Entity API concept)
    - Way to add new entities to GameMap
    - Way to remove entities from GameMap
    - Way to access existing entities on GameMap

*/

#include "entities/entity.hpp"
/**
 * Class responsible for managing all entities in GameMap.
*/
class EntityManager
{
private:

public:
    /**
     * Spawn Entity instance
    */
    void spawnEntity(Entity* ent);
    /**
     * Removes entity from map
    */
    void removeEntity();

    Entity* getEntityByName();
    Vector<Entity*> getAllEntities();
};

#endif // ENTITY_MANAGER_HPP_INCLUDED
