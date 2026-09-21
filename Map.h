#pragma once

#include <string>
#include <vector>

class Map
{
public:
    explicit Map(std::vector<std::string> tiles);

    int GetWidth() const;
    int GetHeight() const;

    float GetPlayerStartX() const;
    float GetPlayerStartY() const;

    bool IsWalkable(int x, int y) const;
    bool CanOccupy(float x, float y, float radius) const;

    const std::string& GetRow(int y) const;

private:
    std::vector<std::string> m_tiles;
    float m_playerStartX;
    float m_playerStartY;
};
