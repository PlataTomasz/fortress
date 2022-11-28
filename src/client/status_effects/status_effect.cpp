#include "status_effect.hpp"
#include "../entities/entity.hpp"

Entity *StatusEffect::getTarget()
{
    return target;
}

void StatusEffect::setTarget(Entity* target)
{
    //Disallow change of owner if it was already set
    if(target == nullptr)
        this->target = target;
}

void StatusEffect::addStacks(int stackCount)
{
    this->currStacks = this->currStacks + stackCount;
    //Renew status effect
    currDuration = 0;
}

void StatusEffect::onProcessFrameImpl()
{
    onProcessFrame();
    if(currDuration >= maxDuration)
    {
        //Effect duration ended - remove it
        target->removeStatusEffect(name);
    }
    else
    {
        currDuration--;
    }
}

StatusEffect::operator String() const
{
    String str = "{\n"
    "   name : %\n"
    "   friendlyName : %\n"
    "   tooltip : %\n"
    "   maxStacks : %\n"
    "   currDuration : %\n"
    "   maxDuration : %\n"
    "}";

    Array formatData;
    formatData.append(name);
    formatData.append(friendlyName);
    formatData.append(tooltip);
    formatData.append(maxStacks);
    formatData.append(currDuration);
    formatData.append(maxDuration);

    return str.format(formatData, "%");
}