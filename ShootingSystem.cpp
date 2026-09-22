#include "ShootingSystem.h"

RayHit ShootingSystem::Shoot(
    const Map& map,
    const Player& player,
    const Raycaster& raycaster) const
{
    return raycaster.CastRay(map, player, 0.0f);
}