#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "ShootingSystem.h"

class HudRenderer
{
public:
    HudRenderer(unsigned int width, unsigned int height);

    void Render(
        sf::RenderWindow& window,
        const Player& player,
        const ShootingSystem& shooting) const;

private:
    unsigned int m_width;
    unsigned int m_height;
};
