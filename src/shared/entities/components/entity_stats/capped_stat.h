#if !defined(CAPPED_ENTITY_STAT_INCLUDED)
#define CAPPED_ENTITY_STAT_INCLUDED

#include "stat.h"

/**
 * Stat which is limited by certain amount - i.e. health
*/
class CappedStat : public Stat
{
GDCLASS(CappedStat, Stat);
private:
    /**
     * Current value of the stat
    */
    double current_value;

    void recalculate()
    {
        Stat::recalculate();

        if(current_value > final_value)
        {
            current_value = final_value;
        }
    }

public:
    void set_current_value(double value)
    {
        //Make sure current value won't exceed max value
        if(value > final_value)
            current_value = final_value;
        else
            current_value = value;
    }

    double get_current_value()
    {
        return current_value;
    }
};

#endif // CAPPED_ENTITY_STAT_INCLUDED
