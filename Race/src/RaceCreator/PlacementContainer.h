#ifndef RAYLIB_CPP_EXAMPLE_PLACEMENTCONTAINER_H
#define RAYLIB_CPP_EXAMPLE_PLACEMENTCONTAINER_H

#include <memory>

enum RacerType
{
    PLAYER,
    BOT
};

class PlacementContainer
{
public:
    PlacementContainer(std::shared_ptr<float> _race_progress, RacerType _type);
    float getRaceProgress();
    RacerType getType();

protected:

private:
    std::shared_ptr<float> race_progress;
    RacerType type;
};

#endif //RAYLIB_CPP_EXAMPLE_PLACEMENTCONTAINER_H
