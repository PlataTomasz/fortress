#include "s_base_entity.h"

bool SBaseEntity::is_equal(SBaseEntity *other)
{
    return (
        this->get_position() == other->get_position()
        && this->get_rotation() == this->get_rotation()
    );
}