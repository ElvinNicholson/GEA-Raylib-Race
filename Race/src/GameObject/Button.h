#ifndef RAYLIB_CPP_EXAMPLE_BUTTON_H
#define RAYLIB_CPP_EXAMPLE_BUTTON_H

#include "raylib-cpp.hpp"
#include "raylib.h"
#include <memory>

class Button
{
public:
    Button(std::string _button_text, raylib::Vector2 _button_pos);
    bool isClicked(raylib::Vector2 mouse_pos);
    void render2D();

protected:

private:
    std::string button_text;
    int button_state;

    raylib::Texture button_texture;
    raylib::Vector2 button_pos;
    raylib::Rectangle button_bounds;
    raylib::Rectangle button_texture_rect;

};


#endif //RAYLIB_CPP_EXAMPLE_BUTTON_H
