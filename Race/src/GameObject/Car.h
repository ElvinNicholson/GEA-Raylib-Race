#ifndef RAYLIB_CPP_EXAMPLE_CAR_H
#define RAYLIB_CPP_EXAMPLE_CAR_H

#include "GameObject.h"
#include <memory>

class Car : public GameObject
{
public:
    Car(std::shared_ptr<raylib::BoundingBox> _player_box);
    void updateCar(float dt);
    raylib::Vector3 getCamPos();

protected:

private:
    void updateBox();

    std::shared_ptr<raylib::BoundingBox> player_box;
    float speed;
    float yaw_cam;
};


#endif //RAYLIB_CPP_EXAMPLE_CAR_H
