#include "orc_leap_slam.h"

#ifdef SERVER
void OrcLeapSlam::_use(const Ref<ActionContext>& action_context) {
    //Check if orc can leap to the target(if it's not too far away - probably separate class)
    
    //Apply status effect that contains leap logic
    //Currently teleports Orc to choosen position
    if(Entity *ent = action_context->get_user()) {
        ent->set_position(action_context->get_target_position());
    }
}

void OrcLeapSlam::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_use", "action_context"), &OrcLeapSlam::_use);
}
#endif

