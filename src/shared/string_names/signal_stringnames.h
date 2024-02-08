#if !defined(SIGNAL_STRINGNAMES_INCLUDED)
#define SIGNAL_STRINGNAMES_INCLUDED

#include <core/string/string_name.h>

class SignalStringNames
{
private:
    static SignalStringNames* singleton;

    SignalStringNames();
protected:
public:
    static SignalStringNames* get_singleton()
    {
        if(!singleton)
        {
            singleton = memnew(SignalStringNames);
        }
        return singleton;
    }

    StringName ON_DAMAGE_TAKEN;
    StringName ON_DAMAGE_DEALT;
    StringName ON_ABILITY_HIT;
    StringName ON_ATTACK_HIT;
    StringName PRE_DEATH;
    StringName ON_DEATH;
    StringName ON_HEALTH_CHANGE;
};

#endif // SIGNAL_STRINGNAMES_INCLUDED