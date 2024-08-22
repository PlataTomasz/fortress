#if !defined(ACTION_HANDLER_INCLUDED)
#define ACTION_HANDLER_INCLUDED

#include <scene/main/node.h>

class Entity;

// Receives RPC describing actions and apply an action effect to the client entity
class EntityActionHandler : public Node {
private:
    Entity *ent = nullptr;

    
};

#endif // ACTION_HANDLER_INCLUDED
