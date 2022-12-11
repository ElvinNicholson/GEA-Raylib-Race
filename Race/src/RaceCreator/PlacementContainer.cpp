#include "PlacementContainer.h"

PlacementContainer::PlacementContainer(std::shared_ptr<float> _race_progress, RacerType _type, std::string _name) :
race_progress(_race_progress), type(_type), name(_name)
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

std::string PlacementContainer::getName()
{
    return name;
}
