#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <classes/node.hpp>
//#include <modules/enet/enet_multiplayer_peer.h>

using namespace godot;

class Client : public Node
{
GDCLASS(Client, Node);
private:

public:

    void _process();
    void _ready();
    void _enter_tree();
protected:
    static void _bind_methods();
public:
    Client();
    ~Client(){};
};

#endif // CLIENT_H_INCLUDED
