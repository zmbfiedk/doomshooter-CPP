#include "Raycaster.h"

#include <algorithm>
#include <cmath>
#include <limits>

Raycaster::Raycaster(float fieldOfViewRadians)
    : m_fieldOfView(fieldOfViewRadians)
{
}

RayHit Raycaster::CastRay(const Map& map, const Player& player, float cameraX) const
{
    const float rotation = player.GetRotation();
    const float directionX = std::sin(rotation);
    const float directionY = std::cos(rotation);
    const float planeLength = std::tan(m_fieldOfView * 0.5f);
    const float planeX = std::cos(rotation) * planeLength;
    const float planeY = -std::sin(rotation) * planeLength;
    const float rayDirectionX = directionX + planeX * cameraX;
    const float rayDirectionY = directionY + planeY * cameraX;

    int mapX = static_cast<int>(std::floor(player.GetX()));
    int mapY = static_cast<int>(std::floor(player.GetY()));

    const float deltaDistanceX = rayDirectionX == 0.0f
        ? std::numeric_limits<float>::max()
        : std::abs(1.0f / rayDirectionX);
    const float deltaDistanceY = rayDirectionY == 0.0f
        ? std::numeric_limits<float>::max()
        : std::abs(1.0f / rayDirectionY);

    const int stepX = rayDirectionX < 0.0f ? -1 : 1;
    const int stepY = rayDirectionY < 0.0f ? -1 : 1;
    float sideDistanceX = rayDirectionX < 0.0f
        ? (player.GetX() - static_cast<float>(mapX)) * deltaDistanceX
        : (static_cast<float>(mapX + 1) - player.GetX()) * deltaDistanceX;
    float sideDistanceY = rayDirectionY < 0.0f
        ? (player.GetY() - static_cast<float>(mapY)) * deltaDistanceY
        : (static_cast<float>(mapY + 1) - player.GetY()) * deltaDistanceY;

    bool verticalWall = false;
    const int maximumSteps = map.GetWidth() * map.GetHeight() + 1;
    for (int steps = 0; steps < maximumSteps; ++steps)
    {
        if (sideDistanceX < sideDistanceY)
        {
            sideDistanceX += deltaDistanceX;
            mapX += stepX;
            verticalWall = true;
        }
        else
        {
            sideDistanceY += deltaDistanceY;
            mapY += stepY;
            verticalWall = false;
        }

        if (!map.IsWalkable(mapX, mapY))
        {
            const float distance = verticalWall
                ? sideDistanceX - deltaDistanceX
                : sideDistanceY - deltaDistanceY;

            return { true, std::max(distance, 0.001f), mapX, mapY, verticalWall };
        }
    }

    return {};
}

std::vector<RayHit> Raycaster::CastView(
    const Map& map,
    const Player& player,
    int screenWidth) const
{
    std::vector<RayHit> hits;
    hits.reserve(screenWidth);

    for (int column = 0; column < screenWidth; ++column)
    {
        const float cameraX = 2.0f * (static_cast<float>(column) + 0.5f)
            / static_cast<float>(screenWidth) - 1.0f;
        hits.push_back(CastRay(map, player, cameraX));
    }

    return hits;
}
