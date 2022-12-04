#include "Gate.h"

Gate::Gate(std::shared_ptr<raylib::Mesh> gate_mesh, std::shared_ptr<raylib::BoundingBox> _player_collider) :
player_collider(_player_collider)
{
    model = LoadModelFromMesh(*gate_mesh);
    scale = 1.0f;
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

    Vector3 size = Vector3Subtract(model.GetBoundingBox().max, model.GetBoundingBox().min);
    float width = size.x/2;
    float height = size.y;
    float breadth = size.z/2;

    bounding_box = BoundingBox{{model_pos.x - width, model_pos.y, model_pos.z},
                               {model_pos.x + width, model_pos.y + height, model_pos.z + (breadth * 2)}};
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
    model.transform = MatrixRotateXYZ((Vector3){0, PI / 2, 0});

    Vector3 size = Vector3Subtract(model.GetBoundingBox().max, model.GetBoundingBox().min);
    float width = size.x/2;
    float height = size.y;
    float breadth = size.z/2;

    bounding_box = BoundingBox{{model_pos.x, model_pos.y, model_pos.z - width},
                               {model_pos.x + (breadth * 2), model_pos.y + height, model_pos.z + width}};
}

void Gate::unloadGate()
{
    // Has to set model to an empty mesh before deletion or else it breaks.
    // Also doest not work when called from deconstructor
    model = LoadModelFromMesh(Mesh());
    model.Unload();
}
