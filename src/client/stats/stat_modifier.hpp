#if !defined(STAT_MODIFIER_HPP_INCLUDED)
#define STAT_MODIFIER_HPP_INCLUDED

#include <cstdio>

/**
 * Stat is object which stores stat value along with It's modifiers, which can be altered by various in-game events
*/
class Stat
{
private:

    /**
     * Initial value of stat - before any modifiers
    */
    double initialValue;

    /**
     * Character stats mostly - Gained per level
    */
    double value;

    /**
     * Flat modifier of stat
    */
    double flatModifier;

    /**
     * % modifier of stat - additive
    */
    double additivePercentageModifier;

    /**
     * % modifier of stat - multiplicative
    */
    double multiplicativePercentageModifier;
public:

    //Setters/Getters
    void setInitialValue(double initialValue)
    {
        this->initialValue = initialValue;
    }

    double getInitialValue()
    {
        return this->initialValue;
    }


    
    void addMultiplicativePercentageModifier(double modifier, bool explicitZeroNegative = false)
    {
        if(modifier > 0)
        {
            multiplicativePercentageModifier*=modifier;
        }
        else if(explicitZeroNegative)
        {
            //To avoid negative stat values where unintended
            multiplicativePercentageModifier*=modifier;
        }
        else
        {
            printf("Adding multiplicative stat modifier failed because of zero or negativ value. Specify explicitZeroNegative if that was desired\n");
        }
    }

    void addAdditivePercentageModifier(double modifier)
    {
        additivePercentageModifier+=modifier;
    }
    //Can be used to subtract stat aswell if value is negative
    void addFlatModifier(double modifier)
    {
        flatModifier+=modifier;
    }
    /**
     * Recalculate stat
    */
    void updateStat()
    {
        value = (initialValue+flatModifier)*(multiplicativePercentageModifier+additivePercentageModifier);
    }

    //TODO: Implement - should increase initialValue
    Stat operator +(double value)
    {
        
    }

    Stat(double initialValue)
    {
        this->initialValue = 0;
        this->value = 0;
        this->flatModifier = 0;
        this->additivePercentageModifier = 0;
        this->multiplicativePercentageModifier = 0;
    }

    ~Stat()
    {

    }

};

#endif // STAT_MODIFIER_HPP_INCLUDED
