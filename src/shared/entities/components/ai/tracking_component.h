#if !defined(TRACKING_COMPONENT_INCLUDED)
#define TRACKING_COMPONENT_INCLUDED

#include "ai_component.h"

class Node3D;

// Component that causes parent to constantly move toward target
class TrackingComponent : public AIComponent {
private:
    // Currently tracked node
    Node3D *target = nullptr;

    void _tick();
};

#endif // TRACKING_COMPONENT_INCLUDED
