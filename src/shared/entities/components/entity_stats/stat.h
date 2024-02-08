#if !defined(ENTITY_STAT_INCLUDED)
#define ENTITY_STAT_INCLUDED

#include <core/error/error_macros.h>
#include <core/object/ref_counted.h>

//TODO: Rename to Attribute - Much more fitting name
class Stat : public RefCounted
{
GDCLASS(Stat, RefCounted);
protected:
    /**
     * Initial value of stat - before any modifiers
    */
    double initial_value = 0;

    /**
     * Final value of stat - after recalculation
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
public:
    /**
     * Recalculate stat final value
    */
    void recalculate()
    {
        this->final_value = (initial_value + flat_modifier) * (1 + multiplicative_percentage_modifier + additive_percentage_modifier);
    }

    //Setters/Getters
    void set_initial_value(double new_initial_value)
    {
        initial_value = new_initial_value;
        recalculate();
    }

    double get_initial_value() const
    {
        return initial_value;
    }

    double get_multiplicative_percentage_modifier() const
    {
        return multiplicative_percentage_modifier;
    }

    double get_additive_percentage_modifier() const
    {
        return additive_percentage_modifier;
    }

    double get_flat_modifier() const
    {
        return flat_modifier;
    }

    /**
     * Returns final value of that stat after all modifiers have applied
    */
    double get_final_value() const
    {
        return final_value;
    }

    void add_multiplicative_percentage_modifier(double modifier, bool explicit_zero_negative = false)
    {
        if(modifier > 0 || explicit_zero_negative)
        {
            multiplicative_percentage_modifier *= modifier;
            recalculate();
        }
        else
        {
            //To avoid negative stat values where unintended
            WARN_PRINT("Adding multiplicative stat modifier failed because of zero or negativ value. Specify explicit_zero_negative if that was desired.");
        }
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

    Stat(double new_initial_value)
    {
        initial_value = new_initial_value;
        recalculate();
    }

    //Empty stat constructor
    Stat()
    {

    }

    ~Stat()
    {

    }
};

#endif // ENTITY_STAT_INCLUDED
