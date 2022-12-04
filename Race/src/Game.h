#ifndef RAYLIB_CPP_EXAMPLE_GAME_H
#define RAYLIB_CPP_EXAMPLE_GAME_H

#include <memory>
#include <iostream>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "cmath"

#include "GameObject/GameObject.h"
#include "GameObject/Car.h"
#include "GameObject/Button.h"
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

    std::unique_ptr<Button> button_lvl1;
    std::unique_ptr<Button> button_lvl2;
    std::unique_ptr<Button> button_reset;
};


#endif //RAYLIB_CPP_EXAMPLE_GAME_H
