#include "Renderer.h"

#include <algorithm>
#include <cmath>

Renderer::Renderer(unsigned int width, unsigned int height)
    : m_width(width),
    m_height(height)
{
}

void Renderer::RenderEnemy(
    sf::RenderWindow& window,
    const Player& player,
    const Enemy& enemy,
    const std::vector<RayHit>& hits) const
{
    if (!enemy.IsAlive())
        return;

    const float rotation = player.GetRotation();
    const float forwardX = std::sin(rotation);
    const float forwardY = std::cos(rotation);
    const float rightX = std::cos(rotation);
    const float rightY = -std::sin(rotation);
    const float relativeX = enemy.GetX() - player.GetX();
    const float relativeY = enemy.GetY() - player.GetY();
    const float depth = relativeX * forwardX + relativeY * forwardY;
    if (depth <= 0.05f)
        return;

    const float planeLength = std::tan(1.0471976f * 0.5f);
    const float cameraX = (relativeX * rightX + relativeY * rightY)
        / (depth * planeLength);
    const int column = static_cast<int>(
        (cameraX + 1.0f) * 0.5f * static_cast<float>(m_width));
    if (column < 0 || column >= static_cast<int>(hits.size()))
        return;

    if (hits[column].hit && depth >= hits[column].distance)
        return;

    const float height = std::min(
        static_cast<float>(m_height) * 1.5f,
        static_cast<float>(m_height) / depth);
    const float width = height * 0.65f;
    sf::RectangleShape body(sf::Vector2f(width, height));
    body.setOrigin(width * 0.5f, height * 0.5f);
    body.setPosition(
        static_cast<float>(column) * m_width / hits.size(),
        static_cast<float>(m_height) * 0.5f);
    body.setFillColor(sf::Color(190, 25, 30));
    window.draw(body);
}

void Renderer::Render(sf::RenderWindow& window, const std::vector<RayHit>& hits) const
{
    window.clear(sf::Color(24, 29, 40));

    sf::RectangleShape floor(sf::Vector2f(
        static_cast<float>(m_width),
        static_cast<float>(m_height) * 0.5f));
    floor.setPosition(0.0f, static_cast<float>(m_height) * 0.5f);
    floor.setFillColor(sf::Color(48, 43, 39));
    window.draw(floor);

    if (hits.empty())
        return;

    const float columnWidth = static_cast<float>(m_width)
        / static_cast<float>(hits.size());
    for (size_t column = 0; column < hits.size(); ++column)
    {
        const RayHit& hit = hits[column];
        if (!hit.hit)
            continue;

        const float wallHeight = std::min(
            static_cast<float>(m_height),
            static_cast<float>(m_height) / hit.distance);
        const float top = (static_cast<float>(m_height) - wallHeight) * 0.5f;
        const float distanceShade = std::min(
            220.0f,
            std::max(35.0f, 220.0f / (hit.distance + 1.0f)));
        const float sideShade = hit.verticalWall ? 0.72f : 1.0f;
        const sf::Uint8 shade = static_cast<sf::Uint8>(distanceShade * sideShade);

        sf::RectangleShape wall(sf::Vector2f(columnWidth + 1.0f, wallHeight));
        wall.setPosition(static_cast<float>(column) * columnWidth, top);
        wall.setFillColor(sf::Color(
            shade,
            static_cast<sf::Uint8>(shade * 0.72f),
            static_cast<sf::Uint8>(shade * 0.52f)));
        window.draw(wall);
    }
}
