#include "mercenary.hpp"
#include <shared/abilities/test_ability.hpp>
#include <shared/helper_macros.h>

#include <shared/entities/components/movement/movement_component.h>

Mercenary::Mercenary()
{

}

void Mercenary::_notification(int notification) {
	switch (notification) {
		case NOTIFICATION_READY:
			print_line("Ready from notification! - Mercenary");
			break;

		case NOTIFICATION_POSTINITIALIZE:
            _init();
			break;

		case NOTIFICATION_PHYSICS_PROCESS:
			_tick();
			break;
	}
}

void Mercenary::_init() {
   //MovementComponent *movement_component = memnew(MovementComponent);
   //add_child(movement_component);
   
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