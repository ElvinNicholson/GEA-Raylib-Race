#ifndef RAYLIB_CPP_EXAMPLE_GATE_H
#define RAYLIB_CPP_EXAMPLE_GATE_H

#include <memory>

#include "raylib-cpp.hpp"
#include "raylib.h"

class Gate
{
public:
    Gate(std::shared_ptr<raylib::Mesh> gate_mesh);
    void render();
    void renderBoundingBox();
    void setPosition(raylib::Vector3 new_position);
    raylib::Vector3 getPosition();
    raylib::Model& getModel();
    bool isColliding(std::shared_ptr<BoundingBox> box);
    void passGate();
    bool isGatePassed();
    void resetLap();
    void rotate90();
    void unloadGate();

protected:

private:
    raylib::BoundingBox bounding_box;

    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::Vector3 model_pos;
    float scale;

    bool passed;

};


#endif //RAYLIB_CPP_EXAMPLE_GATE_H
