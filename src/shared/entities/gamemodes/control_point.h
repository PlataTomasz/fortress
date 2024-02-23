#if !defined(CONTROL_POINT_INCLUDED)
#define CONTROL_POINT_INCLUDED

#include <shared/entities/entity.h>

class ControlPoint : public Entity {
private:
    //TODO: Replace int with TeamID enum
    struct CaptureData {
        int current_capture_team = 0;
        double capture_progress = 0;
    } capture_data;
protected:
    void _notification(int p_notification);
    
    void _tick();
public:
};

#endif // CONTROL_POINT_INCLUDED
