#ifndef RAYLIB_CPP_EXAMPLE_GAME_H
#define RAYLIB_CPP_EXAMPLE_GAME_H

#include <memory>
#include <iostream>

#include "raylib-cpp.hpp"
#include "raylib.h"

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

    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::BoundingBox model_bound;
    raylib::Vector3 model_pos;
    float pitch;
    float yaw;
    float roll;
};


#endif //RAYLIB_CPP_EXAMPLE_GAME_H
