#include "s_base_entity.h"

bool S_BaseEntity::is_equal(S_BaseEntity *other)
{
    return (
        this->get_position() == other->get_position()
        && this->get_rotation() == this->get_rotation()
    );
}