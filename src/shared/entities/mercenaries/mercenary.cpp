#include "mercenary.hpp"
#include <shared/abilities/test_ability.hpp>
#include <shared/helper_macros.h>

Mercenary::Mercenary()
{

}

void Mercenary::_notification(int notification)
{
    switch(notification)
    {
        case NOTIFICATION_READY:
            print_line("Ready from notification! - Mercenary");
        break;

        case NOTIFICATION_PHYSICS_PROCESS:
            _tick();
        break;
    }
}

void Mercenary::initialize()
{
   
}

void Mercenary::_bind_methods()
{

}

void Mercenary::_tick()
{

}

Mercenary::~Mercenary()
{
    
}