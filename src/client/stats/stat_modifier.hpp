#if !defined(STAT_MODIFIER_HPP_INLCUDED)
#define STAT_MODIFIER_HPP_INLCUDED

//TODO: Non existant in module context


/**
 * Stat is object which stores stat value along with It's modifiers, which can be altered by various in-game events.
 * Whenever you change value inside Stat and It's deriving classes, then current_value is recalculated and difference between new and old current_value is returned
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
    double current_value = 0;

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
public:
    /**
     * Recalculate stat final value - returns difference between new and previous final value
    */
    double recalculate()
    {
        double old_current_value = this->current_value;
        this->current_value = (initial_value + flat_modifier) * (multiplicative_percentage_modifier + additive_percentage_modifier);
        return current_value - old_current_value;
    }

    //Setters/Getters
    double set_initial_value(double initial_value)
    {
        this->initial_value = initial_value;
        return this->recalculate();
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

    double get_current_value()
    {
        return this->current_value;
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

        return this->recalculate();
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

        return this->recalculate();
    }

    double add_additive_percentage_modifier(double modifier)
    {
        this->additive_percentage_modifier += modifier;
        return this->recalculate();
    }
    //Can be used to subtract stat aswell if value is negative
    double add_flat_modifier(double modifier)
    {
        this->flat_modifier += modifier;
        return this->recalculate();
    }

    //TODO: Implement - should increase initial_value
    Stat operator +(double value)
    {
        this->initial_value += value;
        this->recalculate();
        return *this;
    }

    //Adding two separate stat object should also sum their modifier percentage values
    Stat operator +(Stat stat)
    {
        this->initial_value += stat.initial_value;
        this->flat_modifier += stat.flat_modifier;
        this->add_additive_percentage_modifier(stat.additive_percentage_modifier);
        this->add_multiplicative_percentage_modifier(stat.multiplicative_percentage_modifier);

        //Will Stat::recalculate() or CompositeStat:recalculate() call in CompositeStat
        this->recalculate();

        return *this;
    }

    //Arithmetiic conversions
    operator double()
    {
        return this->current_value;
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
class CompositeStat : public Stat
{
protected:
    Stat base;
    Stat bonus;

    double recalculate()
    {
        base.recalculate();
        bonus.recalculate();

        double old_current_value = this->current_value;

        //flat_modifier applied on CompositeStat doesn't change anything currently - How It should be applied? As base stat or bonus stat?
        this->current_value = (base.get_current_value() + bonus.get_current_value())*(multiplicative_percentage_modifier + additive_percentage_modifier);
        return current_value - old_current_value;
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

    CompositeStat()
    {

    }

    ~CompositeStat()
    {

    }
};

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

    double recalculate()
    {   
        this->CompositeStat::recalculate();

        double old_current = this->current_value;

        //flat_modifier applied on CompositeStat doesn't change anything currently - How It should be applied? As base stat or bonus stat?
        double new_current = (base.get_current_value() + bonus.get_current_value())*(multiplicative_percentage_modifier + additive_percentage_modifier);
        double new_max = (base.get_current_value() + bonus.get_current_value())*(multiplicative_percentage_modifier + additive_percentage_modifier);

        this->current_value = new_current;

        return current_value - old_current;
    }
};
#endif // STAT_MODIFIER_HPP_INLCUDED
