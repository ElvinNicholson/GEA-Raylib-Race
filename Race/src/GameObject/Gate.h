#ifndef RAYLIB_CPP_EXAMPLE_GATE_H
#define RAYLIB_CPP_EXAMPLE_GATE_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <memory>

class Gate
{
public:
    Gate(std::shared_ptr<raylib::Mesh> gate_mesh, std::shared_ptr<raylib::BoundingBox> _player_collider);
    void render();
    void renderBoundingBox();
    void setPosition(raylib::Vector3 new_position);
    raylib::Vector3 getPosition();
    raylib::Model& getModel();
    bool isPlayerColliding();
    void passGate();
    bool isGatePassed();
    void resetLap();
    void rotate90();

    raylib::BoundingBox bounding_box;

protected:

private:
    std::shared_ptr<raylib::BoundingBox> player_collider;

    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::Vector3 model_pos;
    float scale;

    bool passed;
    float yaw;

};


#endif //RAYLIB_CPP_EXAMPLE_GATE_H
