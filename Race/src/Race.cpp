#include "Race.h"

Race::Race(std::shared_ptr<raylib::BoundingBox> _player_collider) : player_collider(_player_collider)
{
    resetRace();

    waypoint = LoadTexture("../Data/Texture/Waypoint.png");
}

void Race::update(float dt)
{
    if (!isRunning)
    {
        return;
    }

    if (runOnce)
    {
        updateLapsText();
        checkpoints.at(currentGate).setMaterial(active_mat_path.c_str());
        checkpoints.at(nextGate).setMaterial(next_active_mat_path.c_str());

        runOnce = false;
    }


    if ((checkpoints.at(currentGate).isPlayerColliding() && currentGate == 0) ||
        (checkpoints.at(currentGate).isPlayerColliding() && checkpoints.at(lastGate).isGatePassed()))
    {
        std::cout << "Passed Gate " + std::to_string(currentGate) << std::endl;
        checkpoints.at(currentGate).passGate();
        currentGate++;
        lastGate = currentGate - 1;
        nextGate = currentGate + 1;

        if (nextGate > checkpoints.size() - 1)
        {
            nextGate = 0;
        }

        if (currentGate == checkpoints.size())
        {
            finishLap();
        }

        checkpoints.at(lastGate).setMaterial(inactive_mat_path.c_str());
        checkpoints.at(currentGate).setMaterial(active_mat_path.c_str());
        checkpoints.at(nextGate).setMaterial(next_active_mat_path.c_str());
    }

    currentTime += dt;
}

void Race::render2D(Camera camera)
{
    DrawText(TextFormat("Time : %02.02f s", currentTime), 700, 50, 80, BLACK);
    DrawText(lapsText.c_str(), 60, 900, 80, BLACK);

    if (!isRunning)
    {
        return;
    }

    raylib::Vector2 new_pos = GetWorldToScreen(checkpoints.at(currentGate).getPosition(), camera);
    new_pos.x = new_pos.x - 75;
    new_pos.y = new_pos.y - 200;

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 object = Vector3Normalize(Vector3Subtract(camera.position, checkpoints.at(currentGate).getPosition()));
    forward.y = 0;
    object.y = 0;
    float angle = Vector3Angle(forward, object) * RAD2DEG;

    //std::cout << new_pos.x << std::endl;

    if (angle < 140)
    {
        //std::cout << angle << std::endl;
        if (new_pos.x < GetScreenWidth() / 2)
        {
            new_pos.x = 0;
            new_pos.y = GetScreenHeight() / 2 - waypoint.height * 0.3 * 0.5;
        }
        else
        {
            new_pos.x = GetScreenWidth() - waypoint.width * 0.3;
            new_pos.y = GetScreenHeight() / 2 - waypoint.height * 0.3 * 0.5;
        }
    }

    DrawTextureEx(waypoint, new_pos, 0, 0.3, WHITE);
}

void Race::render3D()
{
    for (auto& gate : checkpoints)
    {
        gate.render();
        gate.renderBoundingBox();
    }
}

void Race::resetRace()
{
    runOnce = true;
    isRunning = true;
    isWon = false;
    lapsCurrent = 0;
    currentTime = 0;
    currentGate = 0;
    lastGate = 0;
    nextGate = 1;
}

void Race::finishLap()
{
    std::cout << "Lap Finished!" << std::endl;

    lapsCurrent++;
    if (lapsCurrent > lapsTotal)
    {
        std::cout << "Race Completed!" << std::endl;
        isRunning = false;
        isWon = true;
    }
    updateLapsText();

    currentGate = 0;
    nextGate = 1;

    for (auto& gate : checkpoints)
    {
        gate.resetLap();
    }
}

void Race::setLaps(int number_of_laps)
{
    lapsTotal = number_of_laps;
}


void Race::updateLapsText()
{
    int lap_cur;

    if (lapsCurrent > lapsTotal)
    {
        lap_cur = lapsCurrent;
    }
    else
    {
        lap_cur = lapsCurrent + 1;
    }

    lapsText = "Lap " + std::to_string(lap_cur) + " / " + std::to_string(lapsTotal + 1);
}

void Race::setCheckpoints(int number_of_checkpoints)
{
    for (int i = 0; i < number_of_checkpoints; i++)
    {
        createGate(i);
    }
}

void Race::createGate(int gateNumber)
{
    checkpoints.emplace_back(Gate(model_path, inactive_mat_path, gateNumber, player_collider));
    checkpoints.back().setPosition({0, 0, gateNumber * 20.0f});
}

void Race::setModel(std::string _model_path)
{
    model_path = _model_path;
}

void Race::setInactiveMaterial(std::string _mat_path)
{
    inactive_mat_path = _mat_path;
}

void Race::setActiveMaterial(std::string _mat_path)
{
    active_mat_path = _mat_path;
}

void Race::setNextActiveMaterial(std::string _mat_path)
{
    next_active_mat_path = _mat_path;
}
