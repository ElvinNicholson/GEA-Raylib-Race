#ifndef RAYLIB_CPP_EXAMPLE_RACE_H
#define RAYLIB_CPP_EXAMPLE_RACE_H

#include "GameObject/Gate.h"
#include <memory>
#include <iostream>

class Race
{
public:
    Race(std::shared_ptr<raylib::BoundingBox> _player_collider);
    void update(float dt);
    void render2D();
    void render3D();
    void resetRace();
    void setLaps(int number_of_laps);
    void setCheckpoints(int number_of_checkpoints);
    void setModel(std::string _model_path);
    void setInactiveMaterial(std::string _mat_path);
    void setActiveMaterial(std::string _mat_path);

protected:

private:
    void createGate(int gateNumber);
    void finishLap();
    void updateLapsText();

    std::string model_path;
    std::string inactive_mat_path;
    std::string active_mat_path;

    bool runOnce;
    bool isRunning;
    bool isWon;

    int lapsTotal;
    int lapsCurrent;
    std::string lapsText;

    int currentGate;
    int lastGate;

    float currentTime;

    std::shared_ptr<raylib::BoundingBox> player_collider;
    std::vector<Gate> checkpoints;

};


#endif //RAYLIB_CPP_EXAMPLE_RACE_H
