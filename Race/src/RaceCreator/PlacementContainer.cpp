#include "PlacementContainer.h"

PlacementContainer::PlacementContainer(std::shared_ptr<float> _race_progress, RacerType _type) :
race_progress(_race_progress), type(_type)
{

}

float PlacementContainer::getRaceProgress()
{
    return *race_progress;
}

RacerType PlacementContainer::getType()
{
    return type;
}
