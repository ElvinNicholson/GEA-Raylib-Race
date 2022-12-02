#ifndef RAYLIB_CPP_EXAMPLE_RACE_H
#define RAYLIB_CPP_EXAMPLE_RACE_H

#include "GameObject/Gate.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Race
{
public:
    Race(std::shared_ptr<raylib::BoundingBox> _player_collider);
    void update(float dt);
    void render2D(Camera camera);
    void render3D();
    void resetRace();
    void setLaps(int number_of_laps);
    void setCheckpoints(int number_of_checkpoints);
    void setModel(std::string _model_path);
    void setInactiveMaterial(std::string _mat_path);
    void setActiveMaterial(std::string _mat_path);
    void setNextActiveMaterial(std::string _mat_path);

protected:

private:
    void createGate(int gate_number);
    void finishLap();
    void updateLapsText();
    void setGateActive(int gate_number);
    void setGateInactive(int gate_number);
    void setGateNextActive(int gate_number);
    void readLevel(std::string file_path);

    bool runOnce;
    bool isRunning;
    bool isWon;

    int lapsTotal;
    int lapsCurrent;
    std::string lapsText;

    int currentGate;
    int lastGate;
    int nextGate;

    std::shared_ptr<raylib::Mesh> gate_mesh;
    raylib::Model gate_model;
    raylib::Texture active_texture;
    raylib::Texture next_active_texture;
    raylib::Texture inactive_texture;

    float currentTime;

    std::shared_ptr<raylib::BoundingBox> player_collider;
    std::vector<Gate> checkpoints;

    raylib::Texture waypoint;

};


#endif //RAYLIB_CPP_EXAMPLE_RACE_H
