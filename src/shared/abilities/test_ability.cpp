#include <shared/abilities/test_ability.hpp>


void TestAbility::_use(const Ref<UseContext>& use_context)
{
    print_line("Test ability effect used!");
}

TestAbility::TestAbility()
{
    
}