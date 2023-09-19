#include "game_string_names.h"

GameStringNames* GameStringNames::singleton = nullptr;

GameStringNames::GameStringNames()
{
    ENTITIES_GROUP = StaticCString::create("entities");

    SWORD_MERCENARY = StaticCString::create("sword_mercenary");

}