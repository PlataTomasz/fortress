#if !defined(STAT_MODIFIER_HPP_INCLUDED)
#define STAT_MODIFIER_HPP_INCLUDED

#include <cstdio>

class IStat
{
protected:
    
public:

};

/**
 * Stat is object which stores stat value along with It's modifiers, which can be altered by various in-game events
*/
class Stat
{
protected:

    /**
     * Initial value of stat - before any modifiers
    */
    double initialValue;

    /**
     * Current value of stat - after recalculation
    */
    double totalValue;

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

    double getMultiplicativePercentageModifier()
    {
        return this->multiplicativePercentageModifier;
    }

    double getAdditivePercentageModifier()
    {
        return this->additivePercentageModifier;
    }

    double getFlatModifier()
    {
        return this->flatModifier;
    }

    double getTotalValue()
    {
        return this->totalValue;
    }
    
    void addMultiplicativePercentageModifier(double modifier, bool explicitZeroNegative = false)
    {
        if(modifier > 0)
        {
            this->multiplicativePercentageModifier*=modifier;
        }
        else if(explicitZeroNegative)
        {
            //To avoid negative stat values where unintended
            this->multiplicativePercentageModifier*=modifier;
        }
        else
        {
            printf("Adding multiplicative stat modifier failed because of zero or negativ value. Specify explicitZeroNegative if that was desired\n");
        }
    }

    void addAdditivePercentageModifier(double modifier)
    {
        this->additivePercentageModifier+=modifier;
    }
    //Can be used to subtract stat aswell if value is negative
    void addFlatModifier(double modifier)
    {
        this->flatModifier+=modifier;
    }
    /**
     * Recalculate stat final value
    */
    virtual void updateStat()
    {
        this->totalValue = (initialValue+flatModifier)*(multiplicativePercentageModifier+additivePercentageModifier);
    }

    //TODO: Implement - should increase initialValue
    Stat operator +(double value)
    {
       this->initialValue += value;
       return *this;
    }

    //Adding two separate stat object should also sum their modifier percentage values
    Stat operator +(Stat stat)
    {
        this->initialValue += stat.initialValue;
        this->flatModifier += stat.flatModifier;
        this->addAdditivePercentageModifier(stat.additivePercentageModifier);
        this->addMultiplicativePercentageModifier(stat.multiplicativePercentageModifier);
        
        this->updateStat();

        return *this;
    }

    //Arithmetiic conversions
    operator double()
    {
        return this->totalValue;
    }

    Stat(double initialValue)
    {
      
    }

    //Empty stat constructor
    Stat()
    {
        this->initialValue = 0;
        this->totalValue = 0;
        this->flatModifier = 0;
        this->additivePercentageModifier = 0;
        this->multiplicativePercentageModifier = 0;
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
public:
    const Stat &getBase()
    {
        return base;
    }

    const Stat &getBonus()
    {
        return bonus;
    }

    void updateStat()
    {
        //flatModifier applied on BaseBonusStat doesn't change anything currently - How It should be applied? As base stat or bonus stat?
        this->totalValue = (base.getTotalValue()+bonus.getTotalValue())*(multiplicativePercentageModifier+additivePercentageModifier);
    }

    BaseBonusStat()
    {
        
    }

    ~BaseBonusStat()
    {

    }
};

#endif // STAT_MODIFIER_HPP_INCLUDED
