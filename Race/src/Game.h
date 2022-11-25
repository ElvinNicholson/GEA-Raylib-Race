#ifndef RAYLIB_CPP_EXAMPLE_GAME_H
#define RAYLIB_CPP_EXAMPLE_GAME_H

#include <memory>
#include <iostream>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "cmath"

#include "GameObject/GameObject.h"
#include "GameObject/Car.h"
#include "GameObject/MyBoundingBox.h"

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

    std::unique_ptr<Car> car;
    std::unique_ptr<GameObject> gate;

    std::unique_ptr<MyBoundingBox> box;

    float angle;
};


#endif //RAYLIB_CPP_EXAMPLE_GAME_H
