#if !defined(FIST_MERCENARY_HPP)
#define FIST_MERCENARY_HPP

#include <client/entities/mercenaries/mercenary.hpp>

class FistMercenary : public Mercenary
{
public:
    void _ready() override;
    void _spawn();
    
    FistMercenary();
};

#endif // FIST_MERCENARY_HPP
