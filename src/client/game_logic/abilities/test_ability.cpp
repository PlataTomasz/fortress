#include <client/game_logic/abilities/test_ability.hpp>
#include <variant/utility_functions.hpp>

void TestAbility::use_impl(UseContext use_context)
{
    UtilityFunctions::print("Test ability effect used!");
}

TestAbility::TestAbility()
{
    name = "test_ability";
}