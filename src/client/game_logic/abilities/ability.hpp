#if !defined(ABILITY_HPP_INCLUDED)
#define ABILITY_HPP_INCLUDED

class Ability
{
public:
    virtual void initialize();
    virtual void onCast();
    virtual void onTick();
    virtual void onCooldownChange();
};

#endif // ABILITY_HPP_INCLUDED
