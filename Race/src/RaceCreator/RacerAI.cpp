#include "RacerAI.h"

RacerAI::RacerAI(raylib::Vector3 spawn_pos, float spawn_direction, raylib::Vector4 rgba_color, float _min_angle) :
model_pos(spawn_pos), yaw(spawn_direction), min_angle(_min_angle)
{
    bounding_box = std::make_shared<raylib::BoundingBox>();

    model = LoadModel("../Data/Models/Car3.obj");
    model_texture = LoadTexture("../Data/Materials/car Texture.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;

    updateBox();

    speed = 40;

    current_gate = 0;
    current_lap = 1;

    is_running = true;
    finished_race = false;

    color = raylib::Color((unsigned char)rgba_color.x, (unsigned char)rgba_color.y, (unsigned char)rgba_color.z, (unsigned char)rgba_color.w);
}

void RacerAI::update(float dt, raylib::Vector3 target)
{
    if (!is_running)
    {
        return;
    }

    Vector3 forward = Vector3Normalize(Vector3Subtract(looking_at, model_pos));
    Vector3 object = Vector3Normalize(Vector3Subtract(target, model_pos));

    float angle = Vector3Angle(forward, object) * RAD2DEG;

    float d = (target.x - model_pos.x) * (looking_at.z - model_pos.z) -
              (target.z - model_pos.z) * (looking_at.x - model_pos.x);

    // Decide to turn left or right
    if (d > 0 && angle > min_angle)
    {
        yaw += 1.5;
    }
    else if (d < 0 && angle > min_angle)
    {
        yaw -= 1.5;
    }

    model.transform = MatrixRotateXYZ((Vector3){0, DEG2RAD * yaw, 0});
    looking_at = Vector3{model_pos.x + cos(yaw * DEG2RAD) * 20, 2.5, model_pos.z - sin(yaw * DEG2RAD) * 20};

    Vector3 cur_pos_to_target = Vector3Subtract(target, model_pos);
    float displacement = sqrt(pow(cur_pos_to_target.x, 2) + pow(cur_pos_to_target.z, 2));

    // If car is facing in the general direction or far away from the gate move forward
    if (angle < 45 || displacement > 20)
    {
        move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});
        return;
    }

    // If car is near gate but not looking at it stop moving and turn towards gate
    if (angle > min_angle && displacement > 10)
    {
        return;
    }

    move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});
}

void RacerAI::render()
{
    DrawModel(model, model_pos, 1, color);
}

std::shared_ptr<raylib::BoundingBox> RacerAI::getBoundingBox()
{
    return bounding_box;
}

void RacerAI::updateBox()
{
    raylib::BoundingBox new_box;
    new_box = BoundingBox{{model_pos.x - 2,model_pos.y - 2,model_pos.z - 2},
                          {model_pos.x + 2,model_pos.y + 2,model_pos.z + 2}};

    *bounding_box = new_box;
}

void RacerAI::move(raylib::Vector3 movement)
{
    model_pos = Vector3Add(model_pos, movement);
    updateBox();
}

void RacerAI::setCurrentGate(int gate)
{
    current_gate = gate;
}

int RacerAI::getCurrentGate()
{
    return current_gate;
}

void RacerAI::passGate(int gates_total, int laps_total)
{
    current_gate += 1;
    if (current_gate == gates_total)
    {
        // Finished a lap
        current_gate = 0;

        if (current_lap == laps_total)
        {
            // Finished race
            finished_race = true;
        }

        current_lap += 1;
    }
}
