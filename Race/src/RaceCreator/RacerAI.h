#ifndef RAYLIB_CPP_EXAMPLE_RACERAI_H
#define RAYLIB_CPP_EXAMPLE_RACERAI_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <memory>
#include <iostream>

class RacerAI
{
public:
    RacerAI(raylib::Vector3 spawn_pos, float spawn_direction);
    void update(float dt, raylib::Vector3 target);
    void render();
    std::shared_ptr<raylib::BoundingBox> getBoundingBox();
    void setCurrentGate(int gate);
    int getCurrentGate();

protected:

private:
    void updateBox();
    void move(raylib::Vector3 movement);

    std::shared_ptr<raylib::BoundingBox> bounding_box;
    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::Vector3 model_pos;
    raylib::Vector3 looking_at;

    int currentGate;

    float speed;
    float yaw;

};


#endif //RAYLIB_CPP_EXAMPLE_RACERAI_H
