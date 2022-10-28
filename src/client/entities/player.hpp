#if !defined(PLAYER_HPP_INCLUDED)
#define PLAYER_HPP_INCLUDED

#include "entity.hpp"

class Player : public Entity
{
GDCLASS(Player, Entity);

protected:
    static void _bind_methods(){};
public:
    Player();
    ~Player();
};

#endif // PLAYER_HPP_INCLUDED
