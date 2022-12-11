#include "MinimapContainer.h"

MinimapContainer::MinimapContainer(std::shared_ptr<raylib::Vector3> _bots_pos, std::shared_ptr<float> _bot_direction,raylib::Color _bots_color) :
bots_pos(_bots_pos), bot_direction(_bot_direction), bots_color(_bots_color)
{

}

raylib::Vector3 MinimapContainer::getPos()
{
    return *bots_pos;
}

float MinimapContainer::getDir()
{
    return *bot_direction;
}

raylib::Color MinimapContainer::getColor()
{
    return bots_color;
}
