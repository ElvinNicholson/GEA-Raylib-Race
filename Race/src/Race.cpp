#include "Race.h"

Race::Race(std::shared_ptr<raylib::BoundingBox> _player_collider) : player_collider(_player_collider)
{
    resetRace();
}

void Race::update(float dt)
{
    if (!isRunning)
    {
        return;
    }


    if ((checkpoints.at(currentGate).isPlayerColliding() && currentGate == 0) ||
        (checkpoints.at(currentGate).isPlayerColliding() && checkpoints.at(lastGate).isGatePassed()))
    {
        std::cout << "Passed Gate " + std::to_string(currentGate) << std::endl;
        checkpoints.at(currentGate).passGate();
        currentGate++;
        lastGate = currentGate - 1;

        if (currentGate == checkpoints.size())
        {
            finishLap();
        }
    }
}

void Race::render()
{
    for (auto& gate : checkpoints)
    {
        gate.render();
        gate.renderBoundingBox();
    }
}

void Race::resetRace()
{
    isRunning = true;
    isWon = false;
    lapsCurrent = 0;
    currentTime = 0;
    currentGate = 0;
    lastGate = 0;
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

    currentGate = 0;
    for (auto& gate : checkpoints)
    {
        gate.resetLap();
    }
}

void Race::setLaps(int number_of_laps)
{
    lapsTotal = number_of_laps;
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
    checkpoints.emplace_back(Gate(model_path, mat_path, gateNumber, player_collider));
    checkpoints.back().setPosition({0, 0, gateNumber * 20.0f});
}

void Race::setModel(std::string _model_path)
{
    model_path = _model_path;
}

void Race::setMaterial(std::string _mat_path)
{
    mat_path = _mat_path;
}
