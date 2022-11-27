#include "GameObject.h"

GameObject::GameObject(const char *model_path, const char *material_path)
{
    model = LoadModel(model_path);
    model_texture = LoadTexture(material_path);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;
    model_pos = Vector3 {0, 0, 0};
    pitch = 0.0f;
    yaw = 0.0f;
    roll = 0.0f;
    scale = 1.0f;
}

void GameObject::render()
{
    DrawModel(model, model_pos, scale, WHITE);
}

void GameObject::move(raylib::Vector3 movement)
{
    model_pos = Vector3Add(model_pos, movement);
}

void GameObject::setPosition(raylib::Vector3 new_position)
{
    model_pos = new_position;
}

raylib::Vector3 GameObject::getPosition()
{
    return model_pos;
}

void GameObject::setScale(float _scale)
{
    scale = _scale;
}
