#if !defined(STAT_MODIFIER_HPP_INCLUDED)
#define STAT_MODIFIER_HPP_INCLUDED

#include <cstdio>

/**
 * Stat is object which stores stat value along with It's modifiers, which can be altered by various in-game events.
 * Whenever you change value inside Stat and It's deriving classes, then totalValue is recalculated and difference between new and old totalValue is returned
 * @note Be careful with modifying multiple fields as you need to remember each difference manually
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

    /**
     * Recalculate stat final value - returns difference between new and previous final value
    */
    double recalculateTotalValue()
    {
        double oldTotalValue = this->totalValue;
        this->totalValue = (initialValue+flatModifier)*(multiplicativePercentageModifier+additivePercentageModifier);
        return totalValue - oldTotalValue;
    }
public:

    //Setters/Getters
    double setInitialValue(double initialValue)
    {
        this->initialValue = initialValue;
        return this->recalculateTotalValue();
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

    double addMultiplicativePercentageModifier(double modifier, bool explicitZeroNegative = false)
    {
        if(modifier > 0 || explicitZeroNegative)
        {
            this->multiplicativePercentageModifier*=modifier;
        }
        else
        {
            //To avoid negative stat values where unintended
            printf("Adding multiplicative stat modifier failed because of zero or negativ value. Specify explicitZeroNegative if that was desired\n");
        }

        return this->recalculateTotalValue();
    }

    double subtractMultiplicativePercentageModifier(double modifier, bool explicitNegative = false)
    {
        //Zero can never be passed as method parameter - div by zero
        if(modifier > 0 || (modifier < 0 && explicitNegative))
        {
            this->multiplicativePercentageModifier/=modifier;
        }
        else
        {
            printf("Adding multiplicative stat modifier failed because of zero or negative value. Specify explicitNegative if that was desired\n");
        }

        return this->recalculateTotalValue();
    }

    double addAdditivePercentageModifier(double modifier)
    {
        this->additivePercentageModifier+=modifier;
        return this->recalculateTotalValue();
    }
    //Can be used to subtract stat aswell if value is negative
    double addFlatModifier(double modifier)
    {
        this->flatModifier+=modifier;
        return this->recalculateTotalValue();
    }

    //TODO: Implement - should increase initialValue
    Stat operator +(double value)
    {
        this->initialValue += value;
        this->recalculateTotalValue();
        return *this;
    }

    //Adding two separate stat object should also sum their modifier percentage values
    Stat operator +(Stat stat)
    {
        this->initialValue += stat.initialValue;
        this->flatModifier += stat.flatModifier;
        this->addAdditivePercentageModifier(stat.additivePercentageModifier);
        this->addMultiplicativePercentageModifier(stat.multiplicativePercentageModifier);

        //Will Stat::recalculateTotalValue() or BaseBonusStat:recalculateTotalValue() call in BaseBonusStat
        this->recalculateTotalValue();

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

    double recalculateTotalValue()
    {
        double oldTotalValue = this->totalValue;

        //flatModifier applied on BaseBonusStat doesn't change anything currently - How It should be applied? As base stat or bonus stat?
        this->totalValue = (base.getTotalValue()+bonus.getTotalValue())*(multiplicativePercentageModifier+additivePercentageModifier);
        return totalValue - oldTotalValue;
    }
public:
    const Stat &getBase()
    {
        return base;
    }

    const Stat &getBonus()
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

#endif // STAT_MODIFIER_HPP_INCLUDED
