#include <shared/abilities/test_ability2.hpp>


void TestAbility2::use_impl(UseContext& use_context)
{
    print_line("Test ability 2 effect used!");
}

TestAbility2::TestAbility2()
{
    
}