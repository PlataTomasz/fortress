#include <client/game_logic/abilities/aal/aal_chain_lightning.h>
#include <client/game_logic/collisions/hitbox.h>

void AalChainLightning::use_impl(UseContext use_context)
{
    print_line("Chain Lightning used!");
    /*
    How ability should work?:
    - Target of your choice takes damage
    - Targets near that target takes damage aswell
    */
   
    Entity* ent = nullptr;
    //Vector<Entity*> entities = hitbox->get_colliding_entities();
    TypedArray<Area3D> entities = hitbox->get_overlapping_areas();

    for(int i = 0;i<entities.size();i++)
    {
        
    }

    print_line("Chain Lightning finished!");
}

void AalChainLightning::initialize()
{

}