#ifndef RAYLIB_CPP_EXAMPLE_GAME_H
#define RAYLIB_CPP_EXAMPLE_GAME_H

#include <memory>
#include <iostream>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "cmath"

#include "GameObject/GameObject.h"
#include "GameObject/Car.h"
#include "Race.h"

class Game
{
public:
    Game();
    bool init();
    void update();
    void render();

protected:

private:
    raylib::Camera3D camera;

    std::shared_ptr<raylib::BoundingBox> player_collider;
    std::unique_ptr<Car> car;
    std::unique_ptr<Race> race;
};


#endif //RAYLIB_CPP_EXAMPLE_GAME_H
