#ifndef RAYLIB_CPP_EXAMPLE_RACERAI_H
#define RAYLIB_CPP_EXAMPLE_RACERAI_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <memory>
#include <iostream>

class RacerAI
{
public:
    RacerAI(raylib::Vector3 spawn_pos, float spawn_direction, raylib::Vector4 rgba_color, float _min_angle, std::string _bot_name, std::string _model_path, std::string _mat_path);
    void update(float dt, raylib::Vector3 current_gate_pos, raylib::Vector3 last_gate_pos);
    void render();
    void passGate(int gates_total, int laps_total);
    std::shared_ptr<raylib::BoundingBox> getBoundingBox();
    int getCurrentGate();
    int getLastGate();
    std::shared_ptr<float> getRaceProgress();
    std::shared_ptr<raylib::Vector3> getPosition();
    std::shared_ptr<float> getDirection();
    raylib::Color getColor();
    std::string getName();
    void resetBot(raylib::Vector3 position, float _yaw);

protected:

private:
    void updateBox();
    void move(raylib::Vector3 movement);
    void updateRaceProgress(raylib::Vector3 current_gate_pos, raylib::Vector3 last_gate_pos);

    std::shared_ptr<raylib::BoundingBox> bounding_box;
    raylib::Model model;
    raylib::Texture2D model_texture;
    std::shared_ptr<raylib::Vector3> model_pos;
    raylib::Vector3 looking_at;

    int current_gate;
    int current_lap;
    int last_gate;

    float speed;
    float yaw;
    float min_angle;
    std::shared_ptr<float> direction_angle;

    std::shared_ptr<float> race_progress;

    bool is_running;
    bool finished_race;

    raylib::Color color;

    std::string bot_name;
};


#endif //RAYLIB_CPP_EXAMPLE_RACERAI_H
