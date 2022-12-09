#ifndef RAYLIB_CPP_EXAMPLE_RACERAI_H
#define RAYLIB_CPP_EXAMPLE_RACERAI_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <memory>
#include <iostream>

class RacerAI
{
public:
    RacerAI(raylib::Vector3 spawn_pos, float spawn_direction, raylib::Vector4 rgba_color, float _min_angle);
    void update(float dt, raylib::Vector3 target);
    void render();
    std::shared_ptr<raylib::BoundingBox> getBoundingBox();
    void setCurrentGate(int gate);
    int getCurrentGate();
    void passGate(int gates_total, int laps_total);

protected:

private:
    void updateBox();
    void move(raylib::Vector3 movement);

    std::shared_ptr<raylib::BoundingBox> bounding_box;
    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::Vector3 model_pos;
    raylib::Vector3 looking_at;

    int current_gate;
    int current_lap;

    float speed;
    float yaw;
    float min_angle;

    bool is_running;
    bool finished_race;

    raylib::Color color;

};


#endif //RAYLIB_CPP_EXAMPLE_RACERAI_H
