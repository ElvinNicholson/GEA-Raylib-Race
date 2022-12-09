#include "RacerAI.h"

RacerAI::RacerAI(raylib::Vector3 spawn_pos, float spawn_direction)
{
    bounding_box = std::make_shared<raylib::BoundingBox>();

    model = LoadModel("../Data/Models/Car3.obj");
    model_texture = LoadTexture("../Data/Materials/car Texture.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;

    model_pos = spawn_pos;
    updateBox();

    speed = 40;
    yaw = spawn_direction;

    currentGate = 0;
}

void RacerAI::update(float dt, raylib::Vector3 target)
{
    Vector3 forward = Vector3Normalize(Vector3Subtract(looking_at, model_pos));
    Vector3 object = Vector3Normalize(Vector3Subtract(target, model_pos));

    float angle = Vector3Angle(forward, object) * RAD2DEG;

    float min_angle = 10;

    //float my_angle = atan2(forward.z, -forward.x) * RAD2DEG + 180;
    //float target_angle = atan2(object.z, -object.x) * RAD2DEG + 180;
    //float angle_to_target = my_angle - target_angle;

    //std::cout << "my angle: " + std::to_string(my_angle) << std::endl;
    //std::cout << "target angle: " + std::to_string(target_angle) << std::endl;

    //move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});

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

    // If car is facing in the general direction of the gate move forward
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

//    Vector3 new_pos = Vector3Add(model_pos, {cos(yaw * DEG2RAD) * speed * dt * 10, 0, -sin(yaw * DEG2RAD) * speed * dt * 10});
//    Vector3 new_pos_to_target = Vector3Subtract(target, new_pos);
//    float new_magnitude = pow(new_pos_to_target.x, 2) + pow(new_pos_to_target.z, 2);
//
//
//    if (new_magnitude < displacement)
//    {
//        move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});
//    }

    move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});
}

void RacerAI::render()
{
    DrawModel(model, model_pos, 1, GREEN);
    //DrawLine3D(model_pos, looking_at, GREEN);
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
    currentGate = gate;
}

int RacerAI::getCurrentGate()
{
    return currentGate;
}
