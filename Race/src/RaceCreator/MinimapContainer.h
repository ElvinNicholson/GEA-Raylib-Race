#ifndef RAYLIB_CPP_EXAMPLE_MINIMAPCONTAINER_H
#define RAYLIB_CPP_EXAMPLE_MINIMAPCONTAINER_H

#include "raylib-cpp.hpp"
#include "raylib.h"

#include <memory>

class MinimapContainer
{
public:
    MinimapContainer(std::shared_ptr<raylib::Vector3> _bots_pos, std::shared_ptr<float> _bot_direction, raylib::Color _bots_color);
    raylib::Vector3 getPos();
    float getDir();
    raylib::Color getColor();

protected:

private:
    std::shared_ptr<raylib::Vector3> bots_pos;
    std::shared_ptr<float> bot_direction;
    raylib::Color bots_color;


};


#endif //RAYLIB_CPP_EXAMPLE_MINIMAPCONTAINER_H
