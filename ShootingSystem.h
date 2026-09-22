#pragma once

#include "Map.h"
#include "Player.h"
#include "Raycaster.h"

struct ShootingResult
{
    bool fired = false;
    RayHit hit;
};

class ShootingSystem
{
public:
    ShootingResult Update(
        const Map& map,
        const Player& player,
        const Raycaster& raycaster,
        bool shooting,
        float deltaTime);

private:
    float m_timeUntilNextShot = 0.0f;
    const float m_fireInterval = 0.2f;
};