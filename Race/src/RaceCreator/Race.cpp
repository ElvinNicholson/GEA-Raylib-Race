#include "Race.h"

Race::Race(std::shared_ptr<raylib::BoundingBox> _player_collider, std::string level_data_path) : player_collider(_player_collider)
{
    readLevel(level_data_path);

    gate_model = LoadModelFromMesh(Mesh());
    gate_model.Unload();

    resetRace();
    waypoint = LoadTexture("../Data/Texture/Waypoint.png");
    waypoint_flag = LoadTexture("../Data/Texture/flag.png");
    waypoint_rotation = 0;
    waypoint_scale = 0.3;

    ai_racers.emplace_back(new RacerAI(Vector3{0, 2.5, -20}, -90));
    ai_racers.emplace_back(new RacerAI(Vector3{0, 2.5, -100}, -90));

    minimap.reset(new Minimap());
}

Race::~Race()
{
    for (auto& gate : checkpoints)
    {
        gate->unloadGate();
    }
}

void Race::update(float dt)
{
    minimap->updateMinimap(player_collider->min, checkpoints.at(currentGate)->getPosition(), player_rotation, isRunning);

    if (!isRunning)
    {
        return;
    }

    if (runOnce)
    {
        updateLapsText();

        setAllGateInactive();
        setGateActive(currentGate);
        setGateNextActive(nextGate);

        runOnce = false;
    }


    if ((checkpoints.at(currentGate)->isPlayerColliding() && currentGate == 0) ||
        (checkpoints.at(currentGate)->isPlayerColliding() && checkpoints.at(lastGate)->isGatePassed()))
    {
        timerOn = true;

        std::cout << "Passed Gate " + std::to_string(currentGate) << std::endl;
        checkpoints.at(currentGate)->passGate();
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

        if (isWon)
        {
            setAllGateInactive();
        }
        else
        {
            setGateInactive(lastGate);
            setGateActive(currentGate);
            setGateNextActive(nextGate);
        }
    }

    if (timerOn)
    {
        currentTime += dt;
    }

    for (auto& racer : ai_racers)
    {
        racer->update(dt, checkpoints.at(racer->getCurrentGate())->getPosition());

        if (checkpoints.at(racer->getCurrentGate())->isColliding(racer->getBoundingBox()))
        {
            racer->setCurrentGate(racer->getCurrentGate() + 1);
            if (racer->getCurrentGate() == checkpoints.size())
            {
                racer->setCurrentGate(0);
            }
        }
    }
}

void Race::render2D(Camera camera)
{
    DrawText(TextFormat("Time : %02.02f s", currentTime), 700, 50, 80, BLACK);
    DrawText(lapsText.c_str(), 60, 900, 80, BLACK);

    updateWaypointPos(camera);
    minimap->renderMinimap();

    if (!isRunning)
    {
        return;
    }

    DrawTextureEx(waypoint, waypoint_pos, waypoint_rotation, waypoint_scale, WHITE);
    DrawTextureEx(waypoint_flag, waypoint_flag_pos, 0, waypoint_scale, WHITE);
}

void Race::render3D()
{
    for (auto& gate : checkpoints)
    {
        gate->render();
        gate->renderBoundingBox();
    }

    for (auto& racers : ai_racers)
    {
        racers->render();
    }
}

void Race::resetRace()
{
    runOnce = true;
    timerOn = false;
    isRunning = true;
    isWon = false;
    lapsCurrent = 1;
    currentTime = 0;
    currentGate = 0;
    lastGate = 0;
    nextGate = 1;
}

void Race::finishLap()
{
    std::cout << "Lap Finished!" << std::endl;

    currentGate = 0;
    nextGate = 1;

    lapsCurrent++;
    if (lapsCurrent > lapsTotal)
    {
        std::cout << "Race Completed!" << std::endl;
        isRunning = false;
        isWon = true;
        return;
    }

    updateLapsText();

    for (auto& gate : checkpoints)
    {
        gate->resetLap();
    }
}

void Race::setLaps(int number_of_laps)
{
    lapsTotal = number_of_laps;
}


void Race::updateLapsText()
{
    lapsText = "Lap " + std::to_string(lapsCurrent) + " / " + std::to_string(lapsTotal);
}

void Race::createGate(raylib::Vector3 position, bool rotate)
{
    checkpoints.emplace_back(new Gate(gate_mesh, player_collider));
    checkpoints.back()->setPosition(position);
    if (rotate)
    {
        checkpoints.back()->rotate90();
    }
}

void Race::setModel(std::string _model_path)
{
    // Mesh is deleted when model is deleted
    gate_model = LoadModel(_model_path.c_str());
    gate_mesh = std::make_shared<raylib::Mesh>(gate_model.meshes[0]);
}

void Race::setInactiveMaterial(std::string _mat_path)
{
    inactive_texture = LoadTexture(_mat_path.c_str());
    for (auto& gate : checkpoints)
    {
        gate->getModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = inactive_texture;
    }
}

void Race::setActiveMaterial(std::string _mat_path)
{
    active_texture = LoadTexture(_mat_path.c_str());
}

void Race::setNextActiveMaterial(std::string _mat_path)
{
    next_active_texture = LoadTexture(_mat_path.c_str());
}

void Race::setGateActive(int gate_number)
{
    checkpoints.at(gate_number)->getModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = active_texture;
}

void Race::setGateInactive(int gate_number)
{
    checkpoints.at(gate_number)->getModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = inactive_texture;
}

void Race::setAllGateInactive()
{
    for (int i = 0; i < checkpoints.size(); i++)
    {
        setGateInactive(i);
    }
}

void Race::setGateNextActive(int gate_number)
{
    checkpoints.at(gate_number)->getModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = next_active_texture;
}

void Race::updateWaypointPos(Camera camera)
{
    waypoint_pos = GetWorldToScreen(checkpoints.at(currentGate)->getPosition(), camera);
    waypoint_pos.x = waypoint_pos.x - 75;
    waypoint_pos.y = waypoint_pos.y - 200;
    waypoint_rotation = 0;

    waypoint_flag_pos = Vector2{waypoint_pos.x + 40, waypoint_pos.y + 25};

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 object = Vector3Normalize(Vector3Subtract(camera.position, checkpoints.at(currentGate)->getPosition()));
    forward.y = 0;
    object.y = 0;
    float angle = Vector3Angle(forward, object) * RAD2DEG;

    if (angle < 140)
    {
        float d = (checkpoints.at(currentGate)->getPosition().x - camera.position.x) * (camera.target.z - camera.position.z) -
                  (checkpoints.at(currentGate)->getPosition().z - camera.position.z) * (camera.target.x - camera.position.x);

        if (d >= 0)
        {
            waypoint_pos.x = waypoint.height * waypoint_scale;
            waypoint_pos.y = GetScreenHeight() / 2 - waypoint.width * waypoint_scale * 0.5;
            waypoint_rotation = 90;

            waypoint_flag_pos = Vector2{waypoint_pos.x - 100, waypoint_pos.y + 35};
        }
        else
        {
            waypoint_pos.x = GetScreenWidth() - waypoint.height * waypoint_scale;
            waypoint_pos.y = GetScreenHeight() / 2 + waypoint.width * waypoint_scale * 0.5;
            waypoint_rotation = -90;

            waypoint_flag_pos = Vector2{waypoint_pos.x + 25, waypoint_pos.y - 120};
        }
    }

    player_rotation = atan2(forward.z, -forward.x) * RAD2DEG + 180;
}

void Race::readLevel(std::string file_path)
{
    std::ifstream file(file_path);
    nlohmann::json levelData;
    file >> levelData;

    setLaps(stoi(levelData.value("numberOfLaps", "1")));
    setModel(levelData.value("modelFile", ""));
    setInactiveMaterial(levelData.value("inactiveMaterialFile", ""));
    setActiveMaterial(levelData.value("activeMaterialFile", ""));
    setNextActiveMaterial(levelData.value("nextActiveMaterialFile", ""));


    for (auto& cpData : levelData["checkpoints"])
    {
        std::vector<float> temp_pos;
        temp_pos.reserve(3);
        for (auto& pos : cpData["position"])
        {
            std::string val = pos;
            temp_pos.emplace_back(std::stoi(val));
        }

        raylib::Vector3 position = Vector3{temp_pos.at(0), temp_pos.at(1), temp_pos.at(2)};

        if (cpData.value("facingAxis", "z") == "x")
        {
            createGate(position, true);
        }
        else
        {
            createGate(position, false);
        }
    }

    file.close();
}
