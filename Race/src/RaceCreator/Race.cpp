#include "Race.h"

Race::Race(std::shared_ptr<raylib::BoundingBox> _player_collider, std::string _level_data_path) :
player_collider(_player_collider), level_data_path(_level_data_path)
{
    readLevel(level_data_path);

    gate_model = LoadModelFromMesh(Mesh());
    gate_model.Unload();

    resetRace();
    waypoint = LoadTexture("../Resources/Texture/Waypoint.png");
    waypoint_flag = LoadTexture("../Resources/Texture/flag.png");
    waypoint_rotation = 0;
    waypoint_scale = 0.3;

    minimap.reset(new Minimap());

    player_pos = std::make_shared<raylib::Vector3>(_player_collider->min);
    player_rotation = std::make_shared<float>();

    minimap->addData(player_pos, player_rotation, WHITE);
    for(auto& bots : ai_racers)
    {
        minimap->addData(bots->getPosition(), bots->getDirection(), bots->getColor());
    }

    player_race_progress = std::make_shared<float>();
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
    minimap->updateMinimap(checkpoints.at(currentGate)->getPosition(), isRunning);

    if (!isRunning)
    {
        return;
    }

    if (runOnce)
    {
        createPlacementTable();

        updateLapsText();

        setAllGateInactive();
        setGateActive(currentGate);
        setGateNextActive(nextGate);

        runOnce = false;
    }

    gateHandler();

    if (timerOn)
    {
        currentTime += dt;
    }

    for (auto& bots : ai_racers)
    {
        bots->update(dt, checkpoints.at(bots->getCurrentGate())->getPosition(), checkpoints.at(bots->getLastGate())->getPosition());

        if (checkpoints.at(bots->getCurrentGate())->isColliding(bots->getBoundingBox()))
        {
            bots->passGate(checkpoints.size(), lapsTotal);
        }
    }

    updatePlayerProgress();
    sortPlacementTable();
}

void Race::render2D(Camera camera)
{
    DrawText(TextFormat("Time : %02.02f s", currentTime), 700, 50, 80, BLACK);

    if (isWon)
    {
        displayFinalPlacement();
        return;
    }

    DrawText(lapsText.c_str(), 60, 900, 80, BLACK);
    DrawText(placement_text.c_str(), 60, 800, 80, BLACK);

    minimap->renderMinimap();

    if (!isRunning)
    {
        return;
    }

    updateWaypointPos(camera);
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

    resetBots();
}

void Race::gateHandler()
{
    if ((checkpoints.at(currentGate)->isColliding(player_collider) && currentGate == 0) ||
        (checkpoints.at(currentGate)->isColliding(player_collider) && checkpoints.at(lastGate)->isGatePassed()))
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
    checkpoints.emplace_back(new Gate(gate_mesh));
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
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 object = Vector3Normalize(Vector3Subtract(checkpoints.at(currentGate)->getPosition(), camera.position));
    forward.y = 0;
    object.y = 0;
    float angle = Vector3Angle(forward, object) * RAD2DEG;

    if (angle > camera.fovy * 0.75)
    {
        // Cannot see checkpoint
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
    else
    {
        // Can see checkpoint
        waypoint_pos = GetWorldToScreen(checkpoints.at(currentGate)->getPosition(), camera);
        waypoint_pos.x = waypoint_pos.x - 75;
        waypoint_pos.y = waypoint_pos.y - 200;
        waypoint_rotation = 0;

        waypoint_flag_pos = Vector2{waypoint_pos.x + 40, waypoint_pos.y + 25};
    }

    // Value used for minimap icon rotation
    *player_rotation = atan2(-forward.z, forward.x) * RAD2DEG;
}

void Race::readLevel(std::string file_path)
{
    std::ifstream file(file_path);
    nlohmann::json levelData = nlohmann::json::parse(file);

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

    for (auto& botData : levelData["racingBots"])
    {
        std::vector<float> temp_vec;
        temp_vec.reserve(4);
        for (auto& pos : botData["spawnPosition"])
        {
            std::string val = pos;
            temp_vec.emplace_back(std::stoi(val));
        }

        raylib::Vector3 spawn_pos = Vector3{temp_vec.at(0), temp_vec.at(1), temp_vec.at(2)};

        float spawn_dir = std::stof(botData.value("spawnDirection", "0"));
        float min_angle = std::stof(botData.value("minAngle", "20"));
        std::string bot_name = botData.value("botName", "Bot");
        std::string model_path = botData.value("carModelFile", "");
        std::string mat_path = botData.value("carMaterialFile", "");
        std::string color = botData.value("color", "#FFFFFFFF");

        ai_racers.emplace_back(new RacerAI(spawn_pos, spawn_dir, color, min_angle, bot_name, model_path, mat_path));
    }

    file.close();
}

void Race::resetBots()
{
    std::ifstream file(level_data_path);
    nlohmann::json levelData = nlohmann::json::parse(file);

    int i = 0;
    for (auto& botData : levelData["racingBots"])
    {
        std::vector<float> temp_vec;
        temp_vec.reserve(3);
        for (auto& pos : botData["spawnPosition"])
        {
            std::string val = pos;
            temp_vec.emplace_back(std::stoi(val));
        }

        raylib::Vector3 spawn_pos = Vector3{temp_vec.at(0), temp_vec.at(1), temp_vec.at(2)};

        float spawn_dir = std::stof(botData.value("spawnDirection", "0"));

        ai_racers[i]->resetBot(spawn_pos, spawn_dir);
        i++;
    }

    file.close();
}

void Race::displayFinalPlacement()
{
    if (ai_racers.empty())
    {
        return;
    }

    int x_offset = 1000;
    int i = 1;

    // Only display top 5 racers
    for (auto& placement_data : placements)
    {
        if (i > 5)
        {
            break;
        }

        std::string text = std::to_string(i) + " " + placement_data.getName();

        if (i % 2 == 0)
        {
            DrawRectangle(x_offset, 90 + 100*i, 1000, 100, Fade(LIGHTGRAY, 0.9f));
        }
        else
        {
            DrawRectangle(x_offset, 90 + 100*i, 1000, 100, Fade(LIGHTGRAY, 0.6f));
        }

        raylib::DrawText(text.c_str(), x_offset + 50, 100 + 100*i, 80, BLACK);
        i++;
    }
}

void Race::createPlacementTable()
{
    placements.clear();
    placements.reserve(ai_racers.size() + 1);
    placements.emplace_back(PlacementContainer(player_race_progress, PLAYER, "Player"));

    for (auto& bots : ai_racers)
    {
        placements.emplace_back(bots->getRaceProgress(), BOT, bots->getName());
    }
}

void Race::updatePlayerProgress()
{
    *player_pos = player_collider->max;
    Vector3 cur_pos_to_target = Vector3Subtract(checkpoints.at(currentGate)->getPosition(), *player_pos);
    float car_displacement = sqrt(pow(cur_pos_to_target.x, 2) + pow(cur_pos_to_target.z, 2));

    Vector3 last_to_cur_gate = Vector3Subtract(checkpoints.at(currentGate)->getPosition(), checkpoints.at(lastGate)->getPosition());
    float gate_displacement = sqrt(pow(last_to_cur_gate.x, 2) + pow(last_to_cur_gate.z, 2));

    float displacement_ratio;

    if (gate_displacement == 0)
    {
        displacement_ratio = 0;
    }
    else
    {
        displacement_ratio = 1 - (car_displacement / gate_displacement);
    }

    *player_race_progress = (lapsCurrent * 100) + (currentGate + abs(displacement_ratio));
}

void Race::sortPlacementTable()
{
    placements = quickSort(placements);

    // Get player placement
    int i = 1;
    for (auto& container : placements)
    {
        if (container.getType() == PLAYER)
        {
            break;
        }
        i++;
    }

    placement_text = "Position: " + std::to_string(i);
}

// Quick sort algorithm based on my previous work on Games Tech 101, Worksheet 2, Task 2
std::vector<PlacementContainer> Race::quickSort(std::vector<PlacementContainer> vector)
{
    std::vector<PlacementContainer> lower;
    std::vector<PlacementContainer> higher;
    std::vector<PlacementContainer> equal;

    if (vector.size() > 1)
    {
        float pivot = vector.at(rand() % vector.size()).getRaceProgress();
        for (auto& container : vector)
        {
            if (container.getRaceProgress() < pivot)
            {
                lower.emplace_back(container);
            }
            else if (container.getRaceProgress() > pivot)
            {
                higher.emplace_back(container);
            }
            else
            {
                equal.emplace_back(container);
            }
        }

        return loopRecursiveSort(higher, equal, lower);
    }
    else
    {
        return vector;
    }
}

std::vector<PlacementContainer> Race::loopRecursiveSort(std::vector<PlacementContainer> higher, std::vector<PlacementContainer> equal, std::vector<PlacementContainer> lower)
{
    higher = quickSort(higher);
    lower = quickSort(lower);

    std::vector<PlacementContainer> temp_vector;
    temp_vector.reserve(lower.size() + higher.size() + equal.size());
    temp_vector.insert(temp_vector.end(), higher.begin(), higher.end());
    temp_vector.insert(temp_vector.end(), equal.begin(), equal.end());
    temp_vector.insert(temp_vector.end(), lower.begin(), lower.end());
    return temp_vector;
}
