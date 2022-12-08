#if !defined(GAME_MAP_HPP)
#define GAME_MAP_HPP

#include <scene/3d/node_3d.h>
#include "entities/entity.hpp"

/**
 * GameMap is a Node which should be root of any map.
*/
class GameMap : public Node3D
{
GDCLASS(GameMap, Node3D);

protected:
	static void _bind_methods(){};

private:
    //All entities on the map
    Vector<Entity*> entities;
    Vector<Vector3> redSpawnPoints;
    Vector<Vector3> blueSpawnPoints;
public:
    /**
     * Adds copy of passed entity to GameMap.
    */
    template<class T>
    Entity* addEntityCopy(T* ent)
    {
        T* entCopy = new T(ent);
        addEntity(entCopy);
    }

    Vector<Entity*>& getEntities()
    {
        return this->entities;
    }

    bool hasEntity(Entity* ent)
    {
        return entities.has(ent);
    }

    Entity* getEntityByName(String name)
    {
        //Find entity and return it if it exists
        return nullptr;
    }

    void addEntity(Entity* ent)
    {
        if(!hasEntity(ent))
        {
            //Entity already exists!
            entities.push_back(ent);
            add_child(ent);
        }
    }

    //Event callbacks

    void onChildExitingTree(Node *node)
    {
        //If node that left was entity, delete it from entities that are in map
        if(Entity* ent = Object::cast_to<Entity>(node))
        {
            entities.erase(ent);
        }

        //Otherwise do nothing
    }

    void onReady()
    {
        printf("GameMap ready!");
        connect("child_exiting_tree", callable_mp(this, &GameMap::onChildExitingTree));
        
        //Load spawn points for each team
        Node* redSpawnsNode = get_node(NodePath("SpawnPoints/Red"));
        Node* blueSpawnsNode = get_node(NodePath("SpawnPoints/Blue"));

        if(redSpawnsNode)
        {
            int cc = redSpawnsNode->get_child_count();

            redSpawnPoints.resize(cc);

            for(int i = 0;i<cc;i++)
            {
                Node3D* child = Object::cast_to<Node3D>(redSpawnsNode->get_child(i, false));

                if(child)
                {
                    redSpawnPoints.push_back(child->get_position());
                }
                else
                {
                    //Node {NodeName} has no position - invalid Spawn Point
                }
            }

            printf("Total red spawn points: %d\n", cc);
        }
        else
        {
            printf("No red spawns!");
        }

        if(blueSpawnsNode)
        {
            int cc = blueSpawnsNode->get_child_count();

            blueSpawnPoints.resize(cc);

            for(int i = 0;i<cc;i++)
            {
                Node3D* child = Object::cast_to<Node3D>(blueSpawnsNode->get_child(i, false));

                if(child)
                {
                    blueSpawnPoints.push_back(child->get_position());
                }
                else
                {
                    //Node {NodeName} has no position - invalid Spawn Point
                }
            }

            printf("Total blue spawn points: %d\n", cc);
        }
        else
        {
            printf("No blue spawns!");
        }
    }

    //Getters/Setters

    GameMap()
    {
        if(!Engine::get_singleton()->is_editor_hint())
        {
            //Sizes for entity arrays
            entities.resize(8192);
            entities.resize(32);
            entities.resize(32);

            connect("ready", callable_mp(this, &GameMap::onReady));
        }
    }

    ~GameMap()
    {

    }
};

#endif // GAME_MAP_HPP
