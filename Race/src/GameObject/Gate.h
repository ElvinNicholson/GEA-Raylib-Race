#ifndef RAYLIB_CPP_EXAMPLE_GATE_H
#define RAYLIB_CPP_EXAMPLE_GATE_H

#include "GameObject.h"
#include <memory>

class Gate : public GameObject
{
public:
    Gate(std::shared_ptr<raylib::Mesh> gate_mesh, int _gateNum, std::shared_ptr<raylib::BoundingBox> _player_collider);
    void setPosition(raylib::Vector3 new_position) override;
    void renderBoundingBox();
    bool isPlayerColliding();
    void passGate();
    bool isGatePassed();
    void resetLap();

    raylib::BoundingBox bounding_box;

protected:

private:
    std::shared_ptr<raylib::BoundingBox> player_collider;

    bool passed;
    int gateNum;

};


#endif //RAYLIB_CPP_EXAMPLE_GATE_H
