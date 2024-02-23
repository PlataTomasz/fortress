#if !defined(REALM_INCLUDED)
#define REALM_INCLUDED

#include <scene/main/node.h>

class Game;

//Shared code for Client and Server class
class Realm : public Node {
GDCLASS(Realm, Node);
private:
    void _ready();
protected:
    static Game *game;

    void _notification(int p_notification);
public:
    enum JoinState {
        SERVER_INFO = 1,
        CLIENT_INFO,
    };

    static Game *get_game();
};

VARIANT_ENUM_CAST(Realm::JoinState);

#endif // REALM_INCLUDED
