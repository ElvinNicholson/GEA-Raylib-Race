#ifndef RAYLIB_CPP_EXAMPLE_MINIMAP_H
#define RAYLIB_CPP_EXAMPLE_MINIMAP_H

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#include "MinimapContainer.h"

class Minimap
{
public:
    Minimap();
    void updateMinimap(raylib::Vector3 player_pos, raylib::Vector3 checkpoint_pos, float player_rotation, bool is_running);
    void renderMinimap();
    void addBots(std::shared_ptr<raylib::Vector3> pos, std::shared_ptr<float> dir, raylib::Color color);

protected:

private:
    Shader alpha_discard;
    raylib::RenderTexture2D minimap;
    raylib::Camera3D minimap_cam;
    raylib::Texture minimap_racer;
    raylib::Texture minimap_checkpoint;
    raylib::Rectangle minimap_racer_rect;
    raylib::Rectangle minimap_checkpoint_rect;
    raylib::Vector3 bill_up;

    std::vector<MinimapContainer> bot_data;

};


#endif //RAYLIB_CPP_EXAMPLE_MINIMAP_H
