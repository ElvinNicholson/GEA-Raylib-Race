#include "Gate.h"

Gate::Gate(std::shared_ptr<raylib::Mesh> gate_mesh, std::shared_ptr<raylib::BoundingBox> _player_collider) :
player_collider(_player_collider)
{
    model = LoadModelFromMesh(*gate_mesh);
    scale = 1.0f;
    yaw = 0;
}

void Gate::render()
{
    DrawModel(model, model_pos, scale, WHITE);
}

void Gate::renderBoundingBox()
{
    DrawBoundingBox(bounding_box, GREEN);
}

void Gate::setPosition(raylib::Vector3 new_position)
{
    model_pos = new_position;
    bounding_box = BoundingBox{{model_pos.x - 8, model_pos.y, model_pos.z - 2},
                               {model_pos.x + 8, model_pos.y + 7, model_pos.z + 2}};
}

raylib::Vector3 Gate::getPosition()
{
    return model_pos;
}

raylib::Model& Gate::getModel()
{
    return model;
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

void Gate::rotate90()
{
    yaw = PI / 2;
    model.transform = MatrixRotateXYZ((Vector3){0, yaw, 0});

    bounding_box = BoundingBox{{model_pos.x - 2, model_pos.y, model_pos.z - 8},
                               {model_pos.x + 2, model_pos.y + 7, model_pos.z + 8}};
}
