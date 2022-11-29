#include "Gate.h"

Gate::Gate(std::string model_path, std::string material_path, int _gateNum, std::shared_ptr<raylib::BoundingBox> _player_collider) :
GameObject(model_path.c_str(), material_path.c_str()), gateNum(_gateNum), player_collider(_player_collider)
{

}

void Gate::setPosition(raylib::Vector3 new_position)
{
    GameObject::setPosition(new_position);
    bounding_box = BoundingBox{{model_pos.x - 8, model_pos.y, model_pos.z - 2},
                               {model_pos.x + 8, model_pos.y + 7, model_pos.z + 2}};
}

void Gate::renderBoundingBox()
{
    DrawBoundingBox(bounding_box, GREEN);
}

bool Gate::isPlayerColliding()
{
    if (CheckCollisionBoxes(*player_collider, bounding_box))
    {
        return true;
    }
    return false;
}

void Gate::passGate()
{
    passed = true;
}

bool Gate::isGatePassed()
{
    return passed;
}

void Gate::resetLap()
{
    passed = false;
}

void Gate::setMaterial(const char *material_path)
{
    model_texture = LoadTexture(material_path);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;
}
