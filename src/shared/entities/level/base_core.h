#if !defined(BASE_CORE_INCLUDED)
#define BASE_CORE_INCLUDED

#include <shared/entities/entity.h>

class BaseCore : public Entity {
private:
    void spawn_creep();
protected:
    void _notification(int p_notification);
public:

};

#endif // BASE_CORE_INCLUDED
