#ifndef RAYLIB_CPP_EXAMPLE_CAR_H
#define RAYLIB_CPP_EXAMPLE_CAR_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <memory>

class Car
{
public:
    Car(std::shared_ptr<raylib::BoundingBox> _player_box);
    void updateCar(float dt);
    void render();
    raylib::Vector3 getCamPos();
    raylib::Vector3 getCarPos();

protected:

private:
    void updateBox();
    void move(raylib::Vector3 movement);

    std::shared_ptr<raylib::BoundingBox> player_box;
    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::Vector3 model_pos;


    float speed;
    float yaw_cam;
    float yaw;
};


#endif //RAYLIB_CPP_EXAMPLE_CAR_H
