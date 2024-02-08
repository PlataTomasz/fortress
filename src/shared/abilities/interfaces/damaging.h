#if !defined(DAMAGING_H_INCLUDED)
#define DAMAGING_H_INCLUDED

/**
 * Interface that defines ability which deals damage based on Entity level
*/
class IDamaging
{
private:
    float base_damage = 0;
    float damage_per_level = 0;
public:
    float get_base_damage() { return base_damage; };
    float get_damage_per_level() { return damage_per_level; };
};

#endif // DAMAGING_H_INCLUDED
