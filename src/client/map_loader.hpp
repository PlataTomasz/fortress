#if !defined(MAP_LOADER_H_INCLUDED)
#define MAP_LOADER_H_INCLUDED

/**
 * Class that manages current map. Usually there is no need to alter it.
*/
class MapLoader
{
    static Node *loadMap(String filename);
};

#endif // MAP_LOADER_H_INCLUDED
