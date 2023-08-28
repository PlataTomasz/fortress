#include <client/game_logic/abilities/aal/aal_chain_lightning.h>
#include <client/game_logic/collisions/hitbox.h>

void AalChainLightning::use_impl(UseContext& use_context)
{
    print_line("Chain Lightning used!");

    TypedArray<Area3D> entities = hitbox->get_overlapping_areas();

    for(int i = 0;i<entities.size();i++)
    {
        
    }

    print_line("Chain Lightning finished!");
}

void AalChainLightning::ready_impl()
{

}