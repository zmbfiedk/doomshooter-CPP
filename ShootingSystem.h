#pragma once

#include <array>
#include <cstddef>

#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "Raycaster.h"

struct WeaponStats
{
    int magazineSize;
    int reserveSize;
    int damage;
    float fireInterval;
    float reloadDuration;
};

struct ShootingResult
{
    bool fired = false;
    bool hitEnemy = false;
    bool reloading = false;
    RayHit hit;
};

class ShootingSystem
{
public:
    ShootingResult Update(
        const Map& map,
        const Player& player,
        const Raycaster& raycaster,
        Enemy& enemy,
        bool shooting,
        bool reload,
        float deltaTime);

    void SelectWeapon(std::size_t weaponIndex);
    std::size_t GetSelectedWeapon() const;
    int GetMagazineAmmo() const;
    int GetReserveAmmo() const;
    int GetMagazineSize() const;
    bool IsReloading() const;
    float GetReloadProgress() const;

private:
    static constexpr std::size_t WeaponCount = 3;
    const std::array<WeaponStats, WeaponCount> m_weapons = {{
        {12, 60, 25, 0.25f, 1.0f},
        {6, 30, 50, 0.7f, 1.3f},
        {30, 120, 10, 0.1f, 1.6f}
    }};
    std::array<int, WeaponCount> m_magazineAmmo = {{ 12, 6, 30 }};
    std::array<int, WeaponCount> m_reserveAmmo = {{ 60, 30, 120 }};
    std::size_t m_selectedWeapon = 0;
    float m_timeUntilNextShot = 0.0f;
    float m_reloadRemaining = 0.0f;
};