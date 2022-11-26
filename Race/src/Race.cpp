#include "Race.h"

Race::Race(std::shared_ptr<raylib::BoundingBox> _player_collider) : player_collider(_player_collider)
{
    resetRace();
}

void Race::update(float dt)
{
    checkpoints.at(currentGate).playerCollision();
}

void Race::render()
{
    for (auto& gate : checkpoints)
    {
        gate.render();
    }
}

void Race::resetRace()
{
    isRunning = false;
    isWon = false;
    lapsCurrent = 0;
    currentTime = 0;
    currentGate = 0;
    lastGate = 0;
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
}

void Race::setModel(std::string _model_path)
{
    model_path = _model_path.c_str();
}

void Race::setMaterial(std::string _mat_path)
{
    mat_path = _mat_path.c_str();
}
