#include "Game.h"

Game::Game()
{
    player_collider = std::make_shared<raylib::BoundingBox>();

    car.reset(new Car(player_collider));

    // Initalise race to level 1
    race.reset(new Race(player_collider, "../Resources/LevelData/Level1.json"));

    button_lvl1.reset(new Button("Level 1", Vector2{25, 25}));
    button_lvl2.reset(new Button("Level 2", Vector2{25, 225}));
    button_reset.reset(new Button("Reset", Vector2{325, 25}));
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
    camera.position = car->getCamPos();
    camera.target = car->getCarPos();
    camera.target.y = 4;

    // Call race update function
    race->update(dt);

    if (button_lvl1->isClicked(GetMousePosition()))
    {
        race.reset(new Race(player_collider, "../Resources/LevelData/Level1.json"));
    }

    if (button_lvl2->isClicked(GetMousePosition()))
    {
        race.reset(new Race(player_collider, "../Resources/LevelData/Level2.json"));
    }

    if (button_reset->isClicked(GetMousePosition()))
    {
        race->resetRace();
    }
}

void Game::render()
{
 BeginMode3D(camera);
    car->render();

    // Render race 3D components
    race->render3D();

    DrawGrid(100, 10.f);
 EndMode3D();

    // Render race 2D components
    race->render2D(camera);

    button_lvl1->render2D();
    button_lvl2->render2D();
    button_reset->render2D();
}
