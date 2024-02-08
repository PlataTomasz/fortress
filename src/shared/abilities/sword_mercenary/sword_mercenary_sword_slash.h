#if !defined(SWORD_MERCENARY_SWORD_SLASH_INCLUDED)
#define SWORD_MERCENARY_SWORD_SLASH_INCLUDED

#include <client/game_logic/abilities/ability.hpp>

class SwordMercenarySwordSlash : public Ability
{
protected:
    void use_impl(UseContext& use_context) override;
};

#endif // SWORD_MERCENARY_SWORD_SLASH_INCLUDED
