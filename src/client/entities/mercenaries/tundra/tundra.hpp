#include "../mercenary.hpp"

class Tundra : public Mercenary
{
protected:

public:
    void _ready() override;
    void _spawn();
    Tundra();
};
