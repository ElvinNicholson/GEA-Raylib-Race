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
    PlacementContainer(std::shared_ptr<float> _race_progress, RacerType _type, std::string _name);
    float getRaceProgress();
    RacerType getType();
    std::string getName();

protected:

private:
    std::shared_ptr<float> race_progress;
    RacerType type;
    std::string name;
};

#endif //RAYLIB_CPP_EXAMPLE_PLACEMENTCONTAINER_H
