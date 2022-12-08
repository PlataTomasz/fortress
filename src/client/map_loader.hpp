#if !defined(MAP_LOADER_H_INCLUDED)
#define MAP_LOADER_H_INCLUDED

#include "game_map.hpp"

/**
 * Class that manages current map. Usually there is no need to alter it.
*/
class MapLoader
{
    static GameMap *loadMap(String filename);
};

#endif // MAP_LOADER_H_INCLUDED
