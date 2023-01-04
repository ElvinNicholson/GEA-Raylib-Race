#include "Car.h"
#include <iostream>

Car::Car(std::shared_ptr<raylib::BoundingBox> _player_box) : player_box(_player_box)
{
    model = LoadModel("../Resources/Models/Car3.obj");
    model_texture = LoadTexture("../Resources/Materials/car Texture.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;

    model_pos = Vector3{0, 0, -20};
    speed = 40;

    yaw = -90;
    yaw_cam = -90;
    model.transform = MatrixRotateXYZ((Vector3){0, DEG2RAD * yaw, 0});
}

void Car::updateCar(float dt)
{
    if (IsKeyDown('W'))
    {
        move({cos(yaw * DEG2RAD) * speed * dt, 0, -sin(yaw * DEG2RAD) * speed * dt});
    }
    else if (IsKeyDown('S'))
    {
        move({-cos(yaw * DEG2RAD) * speed * dt/2, 0, sin(yaw * DEG2RAD) * speed * dt/2});
    }

    if (IsKeyDown('A'))
    {
        if (IsKeyDown('S') && !IsKeyDown('W'))
        {
            yaw -= 1.5;
            yaw_cam -= 1.4;
        }
        else
        {
            yaw += 1.5;
            yaw_cam += 1.4;
        }
        model.transform = MatrixRotateXYZ((Vector3){0, DEG2RAD * yaw,0});
    }
    else if (IsKeyDown('D'))
    {
        if (IsKeyDown('S') && !IsKeyDown('W'))
        {
            yaw += 1.5;
            yaw_cam += 1.4;
        }
        else
        {
            yaw -= 1.5;
            yaw_cam -= 1.4;
        }
        model.transform = MatrixRotateXYZ((Vector3){0, DEG2RAD * yaw, 0});
    }
    else
    {
        if (abs(abs(yaw_cam) - abs(yaw)) < 0.9) yaw_cam = yaw;
        else if (yaw_cam > yaw) yaw_cam -= 0.9;
        else if (yaw_cam < yaw) yaw_cam += 0.9;
    }

    updateBox();
}

void Car::render()
{
    DrawModel(model, model_pos, 1, WHITE);
}

raylib::Vector3 Car::getCamPos()
{
    return {model_pos.x - cos(yaw_cam * DEG2RAD) * 20, 7, model_pos.z + sin(yaw_cam * DEG2RAD) * 20};
}

void Car::updateBox()
{
    raylib::BoundingBox new_box;
    new_box = BoundingBox{{model_pos.x - 2,model_pos.y - 2,model_pos.z - 2},
                          {model_pos.x + 2,model_pos.y + 2,model_pos.z + 2}};

    *player_box = new_box;
}

void Car::move(raylib::Vector3 movement)
{
    model_pos = Vector3Add(model_pos, movement);
}

raylib::Vector3 Car::getCarPos()
{
    return model_pos;
}
