#if !defined(C_SYNC_EVENTS_INCLUDED)
#define C_SYNC_EVENTS_INCLUDED

#include <stdint.h>

class Game;

class C_SyncEvent
{
public:
    virtual void execute(Game *game) = 0;
    virtual void deserialize(uint8_t *ptr, uint64_t size) = 0;
};

class C_EntityPositionSyncEvent : public C_SyncEvent
{
private:
    uint64_t ent_netid;
    Vector3 new_position;
public:
    void execute(Game *game) override;
    void deserialize(uint8_t *ptr, uint64_t size) override;
};

#endif // C_SYNC_EVENTS_INCLUDED
