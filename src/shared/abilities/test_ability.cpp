#include <shared/abilities/test_ability.hpp>


void TestAbility::use_impl(UseContext& use_context)
{
    print_line("Test ability effect used!");
}

TestAbility::TestAbility()
{
    
}