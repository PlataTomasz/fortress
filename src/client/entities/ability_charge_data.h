#if !defined(ABILITY_CHARGE_DATA_H_INCLUDED)
#define ABILITY_CHARGE_DATA_H_INCLUDED

//All chargeable abilities should implement
class IChargeable
{
protected:

public:
    double get_maximum_charge_progress();
    double get_current_charge_progress();
};

//Ability casting/channeling
class AbilityChargeData
{
public:
    enum Error
    {
        OK = 0,
        
    };
private:
    IChargeable currently_charged;
    void initialize();
public:
    float charge_progress;
};

#endif // ABILITY_CHARGE_DATA_H_INCLUDED
