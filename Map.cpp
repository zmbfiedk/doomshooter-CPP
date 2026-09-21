#include "Map.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

Map::Map(std::vector<std::string> tiles)
    : m_tiles(std::move(tiles)),
    m_playerStartX(-1.0f),
    m_playerStartY(-1.0f)
{
    if (m_tiles.empty() || m_tiles.front().empty())
        throw std::invalid_argument("Map must contain at least one tile.");

    const size_t width = m_tiles.front().size();
    for (int y = 0; y < GetHeight(); ++y)
    {
        std::string& row = m_tiles[y];
        if (row.size() != width)
            throw std::invalid_argument("Map rows must have the same width.");

        for (int x = 0; x < static_cast<int>(row.size()); ++x)
        {
            char& tile = row[x];
            if (tile == 'P')
            {
                if (m_playerStartX >= 0.0f)
                    throw std::invalid_argument("Map must contain only one player start.");

                m_playerStartX = static_cast<float>(x);
                m_playerStartY = static_cast<float>(y);
                tile = '.';
            }
            else if (tile != '#' && tile != '.')
            {
                throw std::invalid_argument("Map contains an unknown tile.");
            }
        }
    }

    if (m_playerStartX < 0.0f)
        throw std::invalid_argument("Map must contain a player start.");

}

int Map::GetWidth() const
{
    return static_cast<int>(m_tiles.front().size());
}

int Map::GetHeight() const
{
    return static_cast<int>(m_tiles.size());
}

float Map::GetPlayerStartX() const
{
    return m_playerStartX + 0.5f;
}

float Map::GetPlayerStartY() const
{
    return m_playerStartY + 0.5f;
}

bool Map::IsWalkable(int x, int y) const
{
    return x >= 0 && x < GetWidth()
        && y >= 0 && y < GetHeight()
        && m_tiles[y][x] == '.';
}

bool Map::CanOccupy(float x, float y, float radius) const
{
    if (radius < 0.0f)
        return false;

    const int minX = static_cast<int>(std::floor(x - radius));
    const int maxX = static_cast<int>(std::floor(x + radius));
    const int minY = static_cast<int>(std::floor(y - radius));
    const int maxY = static_cast<int>(std::floor(y + radius));

    for (int tileY = minY; tileY <= maxY; ++tileY)
    {
        for (int tileX = minX; tileX <= maxX; ++tileX)
        {
            if (IsWalkable(tileX, tileY))
                continue;

            const float closestX = std::max(
                static_cast<float>(tileX),
                std::min(x, static_cast<float>(tileX + 1)));
            const float closestY = std::max(
                static_cast<float>(tileY),
                std::min(y, static_cast<float>(tileY + 1)));
            const float distanceX = x - closestX;
            const float distanceY = y - closestY;

            if (distanceX * distanceX + distanceY * distanceY < radius * radius)
                return false;
        }
    }

    return true;
}

const std::string& Map::GetRow(int y) const
{
    return m_tiles.at(y);
}
