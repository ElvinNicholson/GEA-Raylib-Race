#include "Gate.h"

Gate::Gate(const char *model_path, const char *material_path, int _gateNum, std::shared_ptr<raylib::BoundingBox> _player_collider) :
GameObject(model_path, material_path), gateNum(_gateNum), player_collider(_player_collider)
{
    setPosition({0, 0, 0});
}

bool Gate::playerCollision()
{
    if (CheckCollisionBoxes(*player_collider, model_box))
    {
        std::cout << "COLLIDE" << std::endl;
        return true;
    }
    return false;
}
