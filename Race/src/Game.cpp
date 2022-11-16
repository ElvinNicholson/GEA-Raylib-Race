#include "Game.h"

Game::Game()
{
}

bool Game::init()
{
    camera = { 0 };
    camera.position = (Vector3){ -170.0f, 100.0f, 0.0f };
    camera.target = (Vector3){ -60.0f, 75.0f, -2.5f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_PERSPECTIVE);

    model = LoadModel("../Data/Models/Car.obj");
    model_texture = LoadTexture("../Data/Materials/car Texture.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model_texture;
    model_bound = GetMeshBoundingBox(model.meshes[0]);
    model_pos = Vector3 {0, 0, 0};
    pitch = 0.0f;
    yaw = 90.0f;
    roll = 0.0f;

    return true;
}

void Game::update()
{
    UpdateCamera(&camera);

    if (IsKeyDown('W'))
    {
        model_pos.x += 10;
        camera.position.x += 10;
        camera.target.x += 10;
    }

    if (IsKeyDown('S'))
    {
        model_pos.x -= 10;
        camera.position.x -= 10;
        camera.target.x -= 10;
    }

    if (IsKeyDown('A'))
    {
        yaw += 1;
    }

    if (IsKeyDown('D'))
    {
        yaw -= 1;
    }

    model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * pitch, DEG2RAD * yaw, DEG2RAD * roll});
}

void Game::render()
{
 BeginMode3D(camera);
    DrawModel(model, model_pos, 1.0f, WHITE);
    DrawGrid(100, 10.f);
 EndMode3D();
}
