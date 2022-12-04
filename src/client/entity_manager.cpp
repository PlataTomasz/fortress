#include "entity_manager.hpp"
#include <scene/main/window.h>

Vector<Entity*> EntityManager::getAllEntities()
{
    Node* entitiesNode = SceneTree::get_singleton()->get_root()->get_child(0)->get_node(NodePath("Game/Map/Entities"));

    Vector<Entity*> entities;

    if(!entitiesNode)
    {
        //Invalid node!
        return entities;
    }
    else
    {
        int childCount = entitiesNode->get_child_count();

        entities.resize(childCount);

        for(int i = 0;i<childCount;i++)
        {
            entities.append((Entity*)entitiesNode->get_child(i));
        }

        return entities;
    }
}