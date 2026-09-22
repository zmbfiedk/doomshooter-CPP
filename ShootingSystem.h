#pragma once

#include "Map.h"
#include "Player.h"
#include "Raycaster.h"

class ShootingSystem
{
public:
    RayHit Shoot(const Map& map, const Player& player, const Raycaster& raycaster) const;
};