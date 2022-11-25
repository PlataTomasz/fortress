#include "status_effect.hpp"
#include "../entities/entity.hpp"

Entity *StatusEffectData::getTarget()
{
    return target;
}

void StatusEffectData::setTarget(Entity* target)
{
    //Disallow change of owner if it was already set
    if(target = nullptr)
        this->target = target;
}

void StatusEffectScript::onProcessFrameImpl()
{
    onProcessFrame();
    if(statusEffectData->currDuration >= statusEffectData->maxDuration)
    {
        //Effect duration ended - remove it
        statusEffectData->target->removeStatusEffect(statusEffectData->name);
    }
    else
    {
        statusEffectData->currDuration--;
    }
}

StatusEffectData::operator String() const
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