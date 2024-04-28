#include <shared/abilities/aal/aal_chain_lightning.h>
#include <shared/collisions/hitbox.h>

void AalChainLightning::_use(const Ref<ActionContext>& action_context)
{
    print_line("Chain Lightning used!");

    TypedArray<Area3D> entities = hitbox->get_overlapping_areas();

    for(int i = 0;i<entities.size();i++)
    {
        
    }

    print_line("Chain Lightning finished!");
}

void AalChainLightning::_ready()
{
    
}