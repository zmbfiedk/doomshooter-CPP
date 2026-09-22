#include "ShootingSystem.h"

#include <algorithm>

ShootingResult ShootingSystem::Update(
    const Map& map,
    const Player& player,
    const Raycaster& raycaster,
    bool shooting,
    float deltaTime)
{
    if (!shooting)
    {
        m_timeUntilNextShot = 0.0f;
        return {};
    }

    if (m_timeUntilNextShot > 0.0f)
    {
        m_timeUntilNextShot = std::max(0.0f, m_timeUntilNextShot - deltaTime);
        return {};
    }

    m_timeUntilNextShot = m_fireInterval;
    return { true, raycaster.CastRay(map, player, 0.0f) };
}