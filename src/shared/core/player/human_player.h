#if !defined(HUMAN_PLAYER_INCLUDED)
#define HUMAN_PLAYER_INCLUDED

#include <shared/core/player.h>

class HumanPlayer : public Player {
GDCLASS(HumanPlayer, Player);
private:
    int owner_peer_id = 0;
public:
    int get_owner_peer_id() {
        return owner_peer_id;
    }

    void set_owner_peer_id(int peer_id) {
        owner_peer_id = peer_id;
    }
};

#endif // HUMAN_PLAYER_INCLUDED
