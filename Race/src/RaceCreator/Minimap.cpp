#include "Minimap.h"

Minimap::Minimap()
{
    alpha_discard = LoadShader(NULL, "../Data/Shaders/billboard.fs");

    minimap = LoadRenderTexture(300, 300);

    minimap_racer = LoadTexture("../Data/Texture/minimap_player.png");
    minimap_racer_rect = Rectangle{0, 0, (float)minimap_racer.width, (float)minimap_racer.height};

    minimap_checkpoint = LoadTexture("../Data/Texture/minimap_checkpoint.png");
    minimap_checkpoint_rect = Rectangle{0, 0, (float)minimap_checkpoint.width, (float)minimap_checkpoint.height};

    bill_up = Vector3{ 1.0f, 0.0f, 0.0f };

    minimap_cam = { 0 };
    minimap_cam.up = Vector3{ 1.0f, 0.0f, 0.0f };
    minimap_cam.fovy = 90.0f;
    minimap_cam.projection = CAMERA_ORTHOGRAPHIC;
    SetCameraMode(minimap_cam, CAMERA_ORTHOGRAPHIC);
}

void Minimap::updateMinimap(raylib::Vector3 checkpoint_pos, bool is_running)
{
    minimap_cam.target = map_data[0].getPos();
    minimap_cam.position = minimap_cam.target;
    minimap_cam.position.y = 20;

    Vector3 cp_pos = checkpoint_pos;
    cp_pos.y = 0;

    cp_pos = Vector3Clamp(cp_pos, Vector3{map_data[0].getPos().x - 35, 0, map_data[0].getPos().z - 35},
                          Vector3{map_data[0].getPos().x + 35, 0, map_data[0].getPos().z + 35});

    BeginTextureMode(minimap);
        BeginMode3D(minimap_cam);
            ClearBackground(GRAY);
            DrawGrid(100, 10.f);
            BeginShaderMode(alpha_discard);
                if (is_running)
                {
                    DrawBillboardPro(minimap_cam, minimap_checkpoint, minimap_checkpoint_rect, cp_pos, bill_up, {20, 20}, {0}, 0, WHITE);
                }
                int i = 0;
                for (auto& data : map_data)
                {
                    float size = 10;
                    if (i == 0)
                    {
                        // Make player icon bigger for readability
                        size = 20;
                    }
                    DrawBillboardPro(minimap_cam, minimap_racer, minimap_racer_rect, data.getPos(), bill_up, {size, size}, {0}, data.getDir(), data.getColor());
                    i++;
                }
            EndShaderMode();
        EndMode3D();
    EndTextureMode();
}

void Minimap::renderMinimap()
{
    DrawTextureRec(minimap.texture, Rectangle{0, 0, (float)minimap.texture.width, (float)-minimap.texture.height}, {(float)GetScreenWidth() - 350, (float)GetScreenHeight() - 350}, WHITE);
}

void Minimap::addData(std::shared_ptr<raylib::Vector3> pos, std::shared_ptr<float> dir, raylib::Color color)
{
    map_data.emplace_back(MinimapContainer(pos, dir, color));
}
