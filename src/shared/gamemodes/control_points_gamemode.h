#if !defined(CONTROL_POINTS_GAMEMODE_INCLUDED)
#define CONTROL_POINTS_GAMEMODE_INCLUDED

#include "gamemode.h"

class ControlPoints : public Gamemode {
GDCLASS(ControlPoints, Gamemode);
private:
    //Store teamid of each mercenary: Maybe introduce TeamComponent?
protected:
public:
};

#endif // CONTROL_POINTS_GAMEMODE_INCLUDED
