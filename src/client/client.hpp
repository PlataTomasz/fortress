#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <scene/main/node.h>
//#include <modules/enet/enet_multiplayer_peer.h>



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
