#include "Game.h"

Game::Game()
{
    car.reset(new Car());
    gate.reset(new GameObject("../Data/Models/Gate.obj", ""));
}

bool Game::init()
{
    camera = { 0 };
    camera.position = (Vector3){ -170.0f, 140.0f, 0.0f };
    camera.target = (Vector3){ -60.0f, 75.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_PERSPECTIVE);

    return true;
}

void Game::update()
{
    UpdateCamera(&camera);

    car->updateCar();
    camera.position = car->getCamPos();
    camera.target = car->getPosition();
    camera.target.y = 4;

    if (CheckCollisionBoxes(car->getBoundingBox(), gate->getBoundingBox()))
    {
        std::cout << "COLLIDE" << std::endl;
    }
}

void Game::render()
{
 BeginMode3D(camera);
    car->render();
    gate->render();
    DrawGrid(100, 10.f);
    DrawBoundingBox(gate->getBoundingBox(), RED);
    DrawBoundingBox(car->getBoundingBox(), BLUE);
 EndMode3D();
}
