#ifndef RAYLIB_CPP_EXAMPLE_RACE_H
#define RAYLIB_CPP_EXAMPLE_RACE_H

#include "GameObject/Gate.h"
#include <memory>

class Race
{
public:
    Race(std::shared_ptr<raylib::BoundingBox> _player_collider);
    void update(float dt);
    void render();
    void resetRace();
    void setLaps(int number_of_laps);
    void setCheckpoints(int number_of_checkpoints);
    void setModel(std::string _model_path);
    void setMaterial(std::string _mat_path);

protected:

private:
    void createGate(int gateNumber);

    const char* model_path;
    const char* mat_path;

    bool isRunning;
    bool isWon;

    int lapsTotal;
    int lapsCurrent;

    int currentGate;
    int lastGate;

    float currentTime;

    std::shared_ptr<raylib::BoundingBox> player_collider;
    std::vector<Gate> checkpoints;

};


#endif //RAYLIB_CPP_EXAMPLE_RACE_H
