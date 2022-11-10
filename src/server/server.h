#if !defined(SERVER_H_INCLUDED)
#define SERVER_H_INCLUDED

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Server : public Node
{
    GDCLASS(Server, Node);
//Networking
private:
    Ref<ENetMultiplayerPeer> networkPeer;
public:
    void _enter_tree();
    void _ready();
protected:
    static void _bind_methods(){};
public:
    Server(){};
    ~Server(){};
};

#endif // SERVER_H_INCLUDED
