#include "Game.h"

Game::Game()
{
    player_collider = std::make_shared<raylib::BoundingBox>();

    car.reset(new Car(player_collider));
    race.reset(new Race(player_collider));
    race->setLaps(1);
    race->setModel("../Data/Models/Gate.obj");
    race->setMaterial("../Data/Materials/Green.png");
    race->setCheckpoints(4);
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
    float dt = GetFrameTime();

    car->updateCar(dt);
    race->update(dt);
    camera.position = car->getCamPos();
    camera.target = car->getPosition();
    camera.target.y = 4;
}

void Game::render()
{
 BeginMode3D(camera);
    car->render();
    race->render3D();
    DrawGrid(100, 10.f);
 EndMode3D();

    race->render2D();
}
