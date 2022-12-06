#ifndef RAYLIB_CPP_EXAMPLE_RACE_H
#define RAYLIB_CPP_EXAMPLE_RACE_H

#include <memory>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include "Gate.h"
#include "Minimap.h"

class Race
{
public:
    Race(std::shared_ptr<raylib::BoundingBox> _player_collider, std::string level_data_path);
    ~Race();
    void update(float dt);
    void render2D(Camera camera);
    void render3D();
    void resetRace();

protected:

private:
    void setLaps(int number_of_laps);
    void setModel(std::string _model_path);
    void setInactiveMaterial(std::string _mat_path);
    void setActiveMaterial(std::string _mat_path);
    void setNextActiveMaterial(std::string _mat_path);
    void createGate(raylib::Vector3 position, bool rotate);

    void finishLap();
    void updateLapsText();

    void setGateActive(int gate_number);
    void setGateInactive(int gate_number);
    void setAllGateInactive();
    void setGateNextActive(int gate_number);

    void updateWaypointPos(Camera camera);

    void readLevel(std::string file_path);

    bool runOnce;
    bool timerOn;
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
    std::vector<std::unique_ptr<Gate>> checkpoints;

    raylib::Texture waypoint;
    raylib::Texture waypoint_flag;
    raylib::Vector2 waypoint_pos;
    raylib::Vector2 waypoint_flag_pos;
    float waypoint_rotation;
    float waypoint_scale;

    std::unique_ptr<Minimap> minimap;
    float player_rotation;

};


#endif //RAYLIB_CPP_EXAMPLE_RACE_H
