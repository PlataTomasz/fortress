#include <shared/abilities/test_ability.hpp>


void TestAbility::_use(const Ref<ActionContext>& action_context)
{
    print_line("Test ability effect used!");
}

TestAbility::TestAbility()
{
    
}