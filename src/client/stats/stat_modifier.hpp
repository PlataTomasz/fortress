#if !defined(STAT_MODIFIER_HPP_INLCUDED)
#define STAT_MODIFIER_HPP_INLCUDED

#include <variant/utility_functions.hpp>

/**
 * Stat is object which stores stat value along with It's modifiers, which can be altered by various in-game events.
 * Whenever you change value inside Stat and It's deriving classes, then total_value is recalculated and difference between new and old total_value is returned
 * @note Be careful with modifying multiple fields as you need to remember each difference manually
*/
class Stat
{
protected:

    /**
     * Initial value of stat - before any modifiers
    */
    double initial_value = 0;

    /**
     * Current value of stat - after recalculation
    */
    double total_value = 0;

    /**
     * Flat modifier of stat
    */
    double flat_modifier = 0;

    /**
     * % modifier of stat - additive
    */
    double additive_percentage_modifier = 0;

    /**
     * % modifier of stat - multiplicative
    */
    double multiplicative_percentage_modifier = 0;

    /**
     * Recalculate stat final value - returns difference between new and previous final value
    */
    double recalculate_total_value()
    {
        double old_total_value = this->total_value;
        this->total_value = (initial_value + flat_modifier) * (multiplicative_percentage_modifier + additive_percentage_modifier);
        return total_value - old_total_value;
    }
public:

    //Setters/Getters
    double set_initial_value(double initial_value)
    {
        this->initial_value = initial_value;
        return this->recalculate_total_value();
    }

    double get_initial_value()
    {
        return this->initial_value;
    }

    double get_multiplicative_percentage_modifier()
    {
        return this->multiplicative_percentage_modifier;
    }

    double get_additive_percentage_modifier()
    {
        return this->additive_percentage_modifier;
    }

    double get_flat_modifier()
    {
        return this->flat_modifier;
    }

    double get_total_value()
    {
        return this->total_value;
    }

    double add_multiplicative_percentage_modifier(double modifier, bool explicit_zero_negative = false)
    {
        if(modifier > 0 || explicit_zero_negative)
        {
            this->multiplicative_percentage_modifier *= modifier;
        }
        else
        {
            //_to avoid negative stat values where unintended
            WARN_PRINT("Adding multiplicative stat modifier failed because of zero or negativ value. Specify explicit_zero_negative if that was desired.");
        }

        return this->recalculate_total_value();
    }

    double subtract_multiplicative_percentage_modifier(double modifier, bool explicit_negative = false)
    {
        //Zero can never be passed as method parameter - div by zero
        if(modifier > 0 || (modifier < 0 && explicit_negative))
        {
            this->multiplicative_percentage_modifier/=modifier;
        }
        else
        {
            WARN_PRINT("Adding multiplicative stat modifier failed because of zero or negative value. Specify explicit_negative if that was desired.");
        }

        return this->recalculate_total_value();
    }

    double add_additive_percentage_modifier(double modifier)
    {
        this->additive_percentage_modifier += modifier;
        return this->recalculate_total_value();
    }
    //Can be used to subtract stat aswell if value is negative
    double add_flat_modifier(double modifier)
    {
        this->flat_modifier += modifier;
        return this->recalculate_total_value();
    }

    //TODO: Implement - should increase initial_value
    Stat operator +(double value)
    {
        this->initial_value += value;
        this->recalculate_total_value();
        return *this;
    }

    //Adding two separate stat object should also sum their modifier percentage values
    Stat operator +(Stat stat)
    {
        this->initial_value += stat.initial_value;
        this->flat_modifier += stat.flat_modifier;
        this->add_additive_percentage_modifier(stat.additive_percentage_modifier);
        this->add_multiplicative_percentage_modifier(stat.multiplicative_percentage_modifier);

        //Will Stat::recalculate_total_value() or BaseBonusStat:recalculate_total_value() call in BaseBonusStat
        this->recalculate_total_value();

        return *this;
    }

    //Arithmetiic conversions
    operator double()
    {
        return this->total_value;
    }

    Stat(double initial_value)
    {
        this->initial_value = initial_value;
    }

    //Empty stat constructor
    Stat()
    {

    }

    ~Stat()
    {

    }

};

/*
Example scenario:
- Health - Current and maximum - missing is not necessary, It can be easily calculated when needed
- Health can also be bonus and base
So in final form:
- currHealth - usualy no modifiers, but for special cases - Stat
- maxHealth - Stat holding two stats
    - baseHealth - Stat
    - bonusHealth - Stat
- This stat might have modifiers that also apply to the total health(both base and bonus)
*/
/**
 * Class storing advanced stats, which consist of base and bonus Stat
*/
class BaseBonusStat : public Stat
{
private:
    Stat base;
    Stat bonus;

    double recalculate_total_value()
    {
        double old_total_value = this->total_value;

        //flat_modifier applied on BaseBonusStat doesn't change anything currently - How It should be applied? As base stat or bonus stat?
        this->total_value = (base.get_total_value() + bonus.get_total_value())*(multiplicative_percentage_modifier + additive_percentage_modifier);
        return total_value - old_total_value;
    }
public:
    const Stat& get_base()
    {
        return base;
    }

    const Stat& get_bonus()
    {
        return bonus;
    }

    BaseBonusStat()
    {

    }

    ~BaseBonusStat()
    {

    }
};

class BaseBonusStatCapped : public BaseBonusStat
{
private:
    double max;
public:
    double get_max()
    {
        return this->max;
    }

    void set_max(double max)
    {
        this->max = max;
    }
};

class HealthStat
{
public:
    double max = 255;
    double current = max;
};
#endif // STAT_MODIFIER_HPP_INLCUDED
