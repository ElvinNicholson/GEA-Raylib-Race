#include "Button.h"

Button::Button(std::string _button_text, raylib::Vector2 _button_pos) : button_text(_button_text), button_pos(_button_pos)
{
    button_state = 0;
    button_texture = LoadTexture("../Data/Texture/button.png");
    button_bounds = Rectangle{button_pos.x, button_pos.y, (float)button_texture.width/2, (float)button_texture.height};
    button_texture_rect = Rectangle{0, 0, (float)button_texture.width/2, (float)button_texture.height};
}

bool Button::isClicked(raylib::Vector2 mouse_pos)
{
    button_state = 0;

    if (CheckCollisionPointRec(mouse_pos, button_bounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            button_state = 1;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            button_texture_rect.x = button_state * button_texture.width / 2;
            return true;
        }
    }

    button_texture_rect.x = button_state * button_texture.width/2;
    return false;
}


void Button::render2D()
{
    DrawTextureRec(button_texture, button_texture_rect, button_pos, WHITE);
    DrawText(button_text.c_str(), button_pos.x + 30 + button_state * 7, button_pos.y + 50 + button_state * 7, 50, BLACK);
}