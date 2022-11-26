#ifndef RAYLIB_CPP_EXAMPLE_GAMEOBJECT_H
#define RAYLIB_CPP_EXAMPLE_GAMEOBJECT_H

#include "raylib-cpp.hpp"
#include "raylib.h"

class GameObject
{
public:
    GameObject(const char *model_path, const char *material_path);
    void render();
    virtual raylib::BoundingBox getBoundingBox();
    void move(raylib::Vector3 movement);
    void setPosition(raylib::Vector3 new_position);
    raylib::Vector3 getPosition();
    void setScale(float _scale);

protected:
    raylib::Model model;
    raylib::Texture2D model_texture;
    raylib::BoundingBox model_box;
    raylib::Vector3 model_pos;
    float pitch;
    float yaw;
    float roll;
    float scale;

private:

};


#endif //RAYLIB_CPP_EXAMPLE_GAMEOBJECT_H
