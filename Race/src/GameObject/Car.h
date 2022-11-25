#ifndef RAYLIB_CPP_EXAMPLE_CAR_H
#define RAYLIB_CPP_EXAMPLE_CAR_H

#include "GameObject.h"

class Car : public GameObject
{
public:
    Car();
    void updateCar();
    raylib::Vector3 getCamPos();
    raylib::BoundingBox getBoundingBox() override;

protected:

private:
    void controls(float dt);

    float speed;
    float yaw_cam;
};


#endif //RAYLIB_CPP_EXAMPLE_CAR_H
