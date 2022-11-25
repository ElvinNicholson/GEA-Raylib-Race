#include "Car.h"
#include <iostream>

Car::Car() : GameObject("../Data/Models/Car3.obj", "../Data/Materials/car Texture.png")
{
    setPosition({0, 2.5, 0});
    speed = 40;
}

void Car::updateCar()
{
    float dt = GetFrameTime();
    controls(dt);

    std::cout << model.transform.m6 << std::endl;
}

raylib::Vector3 Car::getCamPos()
{
    return {model_pos.x - cos(yaw_cam * DEG2RAD) * 20, 7, model_pos.z + sin(yaw_cam * DEG2RAD) * 20};
}

raylib::BoundingBox Car::getBoundingBox()
{
    raylib::BoundingBox new_box;
    new_box = BoundingBox{{model_pos.x - 2,model_pos.y - 2,model_pos.z - 2},
                          {model_pos.x + 2,model_pos.y + 2,model_pos.z + 2}};

    return new_box;
}

void Car::controls(float dt)
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
        model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * pitch, DEG2RAD * yaw, DEG2RAD * roll});
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

        model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * pitch, DEG2RAD * yaw, DEG2RAD * roll});
    }
    else
    {
        if (abs(abs(yaw_cam) - abs(yaw)) < 0.9) yaw_cam = yaw;
        else if (yaw_cam > yaw) yaw_cam -= 0.9;
        else if (yaw_cam < yaw) yaw_cam += 0.9;
    }
}
