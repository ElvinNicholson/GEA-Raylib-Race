#ifndef RAYLIB_CPP_EXAMPLE_GATE_H
#define RAYLIB_CPP_EXAMPLE_GATE_H

#include "GameObject.h"
#include <memory>
#include <iostream>

class Gate : public GameObject
{
public:
    Gate(const char *model_path, const char *material_path, int _gateNum, std::shared_ptr<raylib::BoundingBox> _player_collider);
    bool playerCollision();

protected:

private:
    std::shared_ptr<raylib::BoundingBox> player_collider;

    bool passed;
    bool isColliding;
    int gateNum;

};


#endif //RAYLIB_CPP_EXAMPLE_GATE_H
