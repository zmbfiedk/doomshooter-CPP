#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Raycaster.h"

class Renderer
{
public:
    Renderer(unsigned int width, unsigned int height);

    void Render(sf::RenderWindow& window, const std::vector<RayHit>& hits) const;

private:
    unsigned int m_width;
    unsigned int m_height;
};
