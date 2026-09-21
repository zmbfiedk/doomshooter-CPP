#pragma once

#include <vector>

#include "Map.h"
#include "Player.h"

struct RayHit
{
    bool hit = false;
    float distance = 0.0f;
    int mapX = 0;
    int mapY = 0;
    bool verticalWall = false;
};

class Raycaster
{
public:
    explicit Raycaster(float fieldOfViewRadians = 1.0471976f);

    RayHit CastRay(const Map& map, const Player& player, float cameraX) const;
    std::vector<RayHit> CastView(const Map& map, const Player& player, int screenWidth) const;

private:
    float m_fieldOfView;
};
