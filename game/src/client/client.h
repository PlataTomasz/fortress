#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Client : public Node
{
GDCLASS(Client, Node);
private:
    ENetMultiplayerPeer *multiplayerPeer = nullptr;

    Control *ui = memnew(Control);
    Node *game = nullptr;
public:
    void _process();
    void _ready();
    void _enter_tree();
protected:
    static void _bind_methods();
public:
    Client(){};
    ~Client(){};
};

#endif // CLIENT_H_INCLUDED
