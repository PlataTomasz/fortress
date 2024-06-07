#if !defined(HIT_DATA_INCLUDED  )
#define HIT_DATA_INCLUDED

#include <core/object/ref_counted.h>

class HitData : public RefCounted {
public:
    enum HitType {
        BASIC_ATTACK_HITTYPE,
        ABILITY_HITTYPE,
        OTHER_HITTYPE,
        MAX_HITTYPE
    };
private:
    HitType hit_type;
public:
    HitType get_hit_type() {
        return hit_type;
    }

    HitData(){};
};

#endif // HIT_DATA_INCLUDED
