#if !defined(AI_COMPONENT_INCLUDED)
#define AI_COMPONENT_INCLUDED

#include <server/entities/components/component.h>

/**
 * Component that allows entity to perform actions "on his own".
 * AI is independent of other Entities - It is not omniscient and knows only individual AIComponent context
*/
class AIComponent : public Component
{
    
};

#endif // AI_COMPONENT_INCLUDED
