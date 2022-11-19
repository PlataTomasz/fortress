#include "ability.hpp"
#include "../../entities/throw_ball_projectile.hpp"

#include "../../game.hpp"
#include <scene/main/window.h>

class ThrowBallAbility : public Ability
{
public:
    virtual void initialize()
    {

    };
    virtual void onCast()
    {
        //Retrieve cast context - where is player pointing
        Vector3 targetPos = castContext.getTargetPos();

        ThrowBallProjectile *proj = memnew(ThrowBallProjectile);

        Game *game = (Game*)(SceneTree::get_singleton()->get_root()->get_node(NodePath("Client/Game")));
        proj->set_position(castContext.getCaster()->get_position());
        game->add_child(proj);
        proj->look_at(targetPos);
    };
    virtual void onTick()
    {

    };
    virtual void onCooldownChange()
    {

    };
};