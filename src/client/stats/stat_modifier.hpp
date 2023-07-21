#if !defined(STAT_MODIFIER_HPP_INLCUDED)
#define STAT_MODIFIER_HPP_INLCUDED

#include <core/error/error_macros.h>

class CompositeStat;

/**
 * Stat is object which stores stat value along with It's modifiers, which can be altered by various in-game events.
 * Whenever you change value inside Stat and It's deriving classes, then final_value is recalculated and difference between new and old final_value is returned
 * @note Be careful with modifying multiple fields as you need to remember each difference manually
*/
class Stat
{
protected:
    Stat* parent = nullptr;

    /**
     * Initial value of stat - before any modifiers
    */
    double initial_value = 0;

    /**
     * Current value of stat - after recalculation
    */
    double final_value = 0;

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
     * Last calculated difference in stat value
    */
    double last_recalculate_diff = 0;
public:
    /**
     * Recalculate stat final value - returns difference between new and previous final value
    */
    void recalculate()
    {
        double old_current_value = this->final_value;
        this->final_value = (initial_value + flat_modifier) * (1 + multiplicative_percentage_modifier + additive_percentage_modifier);
        last_recalculate_diff = final_value - old_current_value;

        if(parent != nullptr)
            parent->recalculate();
    }

    //Setters/Getters
    void set_initial_value(double new_initial_value)
    {
        this->initial_value = new_initial_value;
        recalculate();
    }

    double get_initial_value() const
    {
        return this->initial_value;
    }

    double get_multiplicative_percentage_modifier() const
    {
        return this->multiplicative_percentage_modifier;
    }

    double get_additive_percentage_modifier() const
    {
        return additive_percentage_modifier;
    }

    double get_flat_modifier() const
    {
        return this->flat_modifier;
    }

    double get_final_value() const
    {
        return this->final_value;
    }

    void add_multiplicative_percentage_modifier(double modifier, bool explicit_zero_negative = false)
    {
        if(modifier > 0 || explicit_zero_negative)
        {
            this->multiplicative_percentage_modifier *= modifier;
        }
        else
        {
            //To avoid negative stat values where unintended
            WARN_PRINT("Adding multiplicative stat modifier failed because of zero or negativ value. Specify explicit_zero_negative if that was desired.");
        }

        recalculate();
    }

    void subtract_multiplicative_percentage_modifier(double modifier, bool explicit_negative = false)
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

        recalculate();
    }

    void add_additive_percentage_modifier(double modifier)
    {
        additive_percentage_modifier += modifier;
        recalculate();
    }
    //Can be used to subtract stat aswell if value is negative
    void add_flat_modifier(double modifier)
    {
        flat_modifier += modifier;
        recalculate();
    }

    //Arithmetiic conversions
    operator double()
    {
        return final_value;
    }

    Stat(double new_initial_value)
    {
        this->initial_value = new_initial_value;
        this->recalculate();
    }

    //Empty stat constructor
    Stat()
    {

    }

    ~Stat()
    {

    }

    friend CompositeStat;

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

class CompositeStat : public Stat
{
protected:
    Stat base;
    Stat bonus;
public:
    void recalculate()
    {
        double old_current_value = this->final_value;

        this->final_value = (base.get_final_value() + bonus.get_final_value())*(1 + multiplicative_percentage_modifier)*(1 + additive_percentage_modifier);
        last_recalculate_diff = final_value - old_current_value;
    }

    Stat& get_base()
    {
        return base;
    }

    Stat& get_bonus()
    {
        return bonus;
    }

    Stat& operator=(const double& value)
    {
        initial_value = value;
        return *this;
    }
    

    CompositeStat()
    {
        base.parent = this;
        bonus.parent = this;
    }

    ~CompositeStat()
    {

    }
};

class CappedCompositeStat : CompositeStat
{
public:
    void set_max_total_value();
    void set_max_initial_value(); 
};


class HealthStat : public Stat
{
protected:
    double current_value = 0;
    CompositeStat max;
public:
    void set_current_value(double new_value)
    {
        double max_health = max.get_final_value();
        if(new_value > max_health)
        {
            new_value = max_health;
        }

        current_value = new_value;
    }

    const double& get_current_value()
    {
        return current_value;
    }

    void recalculate()
    {
        double old_current_value = this->final_value;
        this->final_value = (initial_value + flat_modifier) * ( 1 + multiplicative_percentage_modifier)*(1 + additive_percentage_modifier);

        //Cap current health, so it never exceed maximum
        if(current_value > max.get_final_value())
        {
            current_value = max.get_final_value();
        }

        last_recalculate_diff = final_value - old_current_value;


    }

    CompositeStat& get_max_health_stat()
    {
        return max;
    }
};

/*

class CompositeStatCapped : public CompositeStat
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
        //TODO: Emit max health change signal
    }

    void recalculate()
    {   
        this->CompositeStat::recalculate();

        double old_current = this->final_value;

        //flat_modifier applied on CompositeStat doesn't change anything currently - How It should be applied? As base stat or bonus stat?
        double new_current = (base.get_final_value() + bonus.get_final_value())*(multiplicative_percentage_modifier + additive_percentage_modifier);

        double new_max = (base.get_final_value() + bonus.get_final_value())*(multiplicative_percentage_modifier + additive_percentage_modifier);

        this->final_value = new_current;

        return final_value - old_current;
    }
};
*/
#endif // STAT_MODIFIER_HPP_INLCUDED
