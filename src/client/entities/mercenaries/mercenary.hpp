#if !defined(MERCENARY_HPP_INCLUDED)
#define MERCENARY_HPP_INCLUDED

#include "../entity.hpp"

/**
 * Mercenary is a class responsible for representing
 * specialization of entity which is primarily supposed
 * to be controlled by Player.
*/
class Mercenary : public Entity
{
GDCLASS(Mercenary, Entity);

private:

protected:
    

    static void _bind_methods(){};
public:
    Mercenary(){};
    ~Mercenary(){};
};

#endif // MERCENARY_HPP_INCLUDED