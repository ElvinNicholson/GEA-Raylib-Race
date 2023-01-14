#include "RacerAI.h"

RacerAI::RacerAI(raylib::Vector3 spawn_pos, float spawn_direction, std::string _color_hex, float _min_angle, std::string _bot_name, std::string _model_path, std::string _mat_path) :
yaw(spawn_direction), min_angle(_min_angle), bot_name(_bot_name)
{
    bounding_box = std::make_shared<raylib::BoundingBox>();

    model_pos = std::make_shared<raylib::Vector3>(spawn_pos);
    model = LoadModel(_model_path.c_str());
    model_texture = LoadTexture(_mat_path.c_str());
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;

    updateBox();

    speed = 40;

    last_gate = 0;
    current_gate = 0;
    current_lap = 1;

    is_running = true;
    finished_race = false;

    int r;
    int g;
    int b;
    int a;
    char const* color_hex = _color_hex.c_str();
    std::sscanf(color_hex, "#%02x%02x%02x%02x", &a, &r, &g, &b);

    color = raylib::Color(r, g, b, a);

    race_progress = std::make_shared<float>();
    direction_angle = std::make_shared<float>();
}

void RacerAI::update(float dt, raylib::Vector3 current_gate_pos, raylib::Vector3 last_gate_pos)
{
    if (!is_running)
    {
        return;
    }

    Vector3 forward = Vector3Normalize(Vector3Subtract(looking_at, *model_pos));
    Vector3 target = Vector3Subtract(current_gate_pos, *model_pos);

    float angle = Vector3Angle(forward, target) * RAD2DEG;
    *direction_angle = atan2(-forward.z, forward.x) * RAD2DEG;

    float d = (current_gate_pos.x - model_pos->x) * (looking_at.z - model_pos->z) -
              (current_gate_pos.z - model_pos->z) * (looking_at.x - model_pos->x);

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
    looking_at = Vector3{model_pos->x + cos(yaw * DEG2RAD) * 20, 2.5, model_pos->z - sin(yaw * DEG2RAD) * 20};

    float displacement = sqrt(pow(target.x, 2) + pow(target.z, 2));

    updateRaceProgress(current_gate_pos, last_gate_pos);

    // If car is facing in the general direction or far away from the gate move forward
    // If car is near gate but not looking at it stop moving and turn towards gate
    if ((angle < 45 || displacement > 20) || !(angle > min_angle && displacement > 10))
    {
        move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});
        return;
    }
}

void RacerAI::render()
{
    DrawModel(model, *model_pos, 1, WHITE);
}

std::shared_ptr<raylib::BoundingBox> RacerAI::getBoundingBox()
{
    return bounding_box;
}

void RacerAI::updateBox()
{
    raylib::BoundingBox new_box;
    new_box = BoundingBox{{model_pos->x - 2,model_pos->y - 2,model_pos->z - 2},
                          {model_pos->x + 2,model_pos->y + 2,model_pos->z + 2}};

    *bounding_box = new_box;
}

void RacerAI::move(raylib::Vector3 movement)
{
    *model_pos = Vector3Add(*model_pos, movement);
    updateBox();
}

int RacerAI::getCurrentGate()
{
    return current_gate;
}

int RacerAI::getLastGate()
{
    return last_gate;
}

void RacerAI::passGate(int gates_total, int laps_total)
{
    current_gate += 1;
    last_gate = current_gate - 1;
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

std::shared_ptr<float> RacerAI::getRaceProgress()
{
    return race_progress;
}

void RacerAI::updateRaceProgress(raylib::Vector3 current_gate_pos, raylib::Vector3 last_gate_pos)
{
    Vector3 cur_pos_to_target = Vector3Subtract(current_gate_pos, *model_pos);
    float car_displacement = sqrt(pow(cur_pos_to_target.x, 2) + pow(cur_pos_to_target.z, 2));

    Vector3 last_to_cur_gate = Vector3Subtract(current_gate_pos, last_gate_pos);
    float gate_displacement = sqrt(pow(last_to_cur_gate.x, 2) + pow(last_to_cur_gate.z, 2));

    float displacement_ratio;

    if (gate_displacement == 0)
    {
        displacement_ratio = 0;
    }
    else
    {
        displacement_ratio = 1 - (car_displacement / gate_displacement);
    }

    *race_progress = (current_lap * 100) + (current_gate + abs(displacement_ratio));
}

std::string RacerAI::getName()
{
    return bot_name;
}

std::shared_ptr<raylib::Vector3> RacerAI::getPosition()
{
    return model_pos;
}

void RacerAI::resetBot(raylib::Vector3 position, float _yaw)
{
    *model_pos = position;
    yaw = _yaw;

    last_gate = 0;
    current_gate = 0;
    current_lap = 1;

    is_running = true;
    finished_race = false;
}

raylib::Color RacerAI::getColor()
{
    return color;
}

std::shared_ptr<float> RacerAI::getDirection()
{
    return direction_angle;
}
