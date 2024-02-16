#if !defined(LEVEL_ENTITIES_INCLUDED)
#define LEVEL_ENTITIES_INCLUDED

#include <scene/main/node.h>

//Stores all entities present on level
class Entities : public Node {
private:

protected:
    void _notification(int p_notification);
public:

};

#endif // LEVEL_ENTITIES_INCLUDED
