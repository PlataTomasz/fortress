#if !defined(GAMESTATE_INCLUDED)
#define GAMESTATE_INCLUDED

#include <core/templates/hash_map.h>
#include <core/variant/variant.h>

//TODO: Implement Gamestate

class NetworkingDatatable
{

};

struct EntityField
{
    uint8_t field_id;
    Variant value;
};

typedef Vector<EntityField> EntityFields;

class S_Game;

/**
 * Same as GamestateSnapshot, but only minimal set of information is stored - mostly used for differnce between two GamestateSnapshot objects
*/
class GamestateDelta
{
private:
    //I'll just use Variant, saves a lot of trouble
    HashMap<uint64_t, EntityFields> entities;
public:
    Vector<uint8_t> serialize()
    {
        
        return Vector<uint8_t>();
    };

    void serialize(const uint8_t *data, uint64_t size);
};

/**
 * Gamestate snapshot is a class which object store FULL information about current state of game, such as entities, values of their fields, etc.
*/
class GamestateSnapshot
{
private:
    //When gamestate was created?
    uint64_t frame;
    //List of all entities and fields associated with them
    HashMap<uint64_t, EntityFields> entities;
public:
    GamestateDelta diff(GamestateSnapshot& other);

    //game - for which game object, gamestate should be generated?
    GamestateSnapshot(S_Game *game);
};

#endif // GAMESTATE_INCLUDED
