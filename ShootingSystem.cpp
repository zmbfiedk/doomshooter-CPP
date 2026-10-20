#include "ShootingSystem.h"

#include <algorithm>
#include <cmath>

ShootingResult ShootingSystem::Update(
    const Map& map,
    const Player& player,
    const Raycaster& raycaster,
    Enemy& enemy,
    bool shooting,
    bool reload,
    float deltaTime)
{
    if (!player.IsAlive())
        return {};

    if (m_reloadRemaining > 0.0f)
    {
        m_reloadRemaining = std::max(0.0f, m_reloadRemaining - deltaTime);
        if (m_reloadRemaining == 0.0f)
        {
            const WeaponStats& weapon = m_weapons[m_selectedWeapon];
            const int needed = weapon.magazineSize - m_magazineAmmo[m_selectedWeapon];
            const int loaded = std::min(needed, m_reserveAmmo[m_selectedWeapon]);
            m_magazineAmmo[m_selectedWeapon] += loaded;
            m_reserveAmmo[m_selectedWeapon] -= loaded;
        }
        return { false, false, true, {} };
    }

    const WeaponStats& weapon = m_weapons[m_selectedWeapon];
    if (reload || (shooting && m_magazineAmmo[m_selectedWeapon] == 0))
    {
        if (m_magazineAmmo[m_selectedWeapon] < weapon.magazineSize
            && m_reserveAmmo[m_selectedWeapon] > 0)
        {
            m_reloadRemaining = weapon.reloadDuration;
            return { false, false, true, {} };
        }
    }

    m_timeUntilNextShot = std::max(0.0f, m_timeUntilNextShot - deltaTime);
    if (!shooting || m_timeUntilNextShot > 0.0f
        || m_magazineAmmo[m_selectedWeapon] == 0)
        return {};

    m_timeUntilNextShot = weapon.fireInterval;
    --m_magazineAmmo[m_selectedWeapon];

    const RayHit wallHit = raycaster.CastRay(map, player, 0.0f);
    const float directionX = std::sin(player.GetRotation());
    const float directionY = std::cos(player.GetRotation());
    const float relativeX = enemy.GetX() - player.GetX();
    const float relativeY = enemy.GetY() - player.GetY();
    const float enemyDistance = relativeX * directionX + relativeY * directionY;
    const float perpendicular = std::abs(
        relativeX * directionY - relativeY * directionX);
    const bool enemyHit = enemy.IsAlive()
        && enemyDistance > 0.0f
        && perpendicular <= enemy.GetRadius()
        && (!wallHit.hit || enemyDistance < wallHit.distance);
    if (enemyHit)
        enemy.TakeDamage(static_cast<float>(weapon.damage));

    return { true, enemyHit, false, wallHit };
}

void ShootingSystem::SelectWeapon(std::size_t weaponIndex)
{
    if (weaponIndex < WeaponCount && weaponIndex != m_selectedWeapon)
    {
        m_selectedWeapon = weaponIndex;
        m_timeUntilNextShot = 0.0f;
        m_reloadRemaining = 0.0f;
    }
}

std::size_t ShootingSystem::GetSelectedWeapon() const { return m_selectedWeapon; }
int ShootingSystem::GetMagazineAmmo() const { return m_magazineAmmo[m_selectedWeapon]; }
int ShootingSystem::GetReserveAmmo() const { return m_reserveAmmo[m_selectedWeapon]; }
int ShootingSystem::GetMagazineSize() const { return m_weapons[m_selectedWeapon].magazineSize; }
bool ShootingSystem::IsReloading() const { return m_reloadRemaining > 0.0f; }
float ShootingSystem::GetReloadProgress() const
{
    if (!IsReloading())
        return 0.0f;
    return 1.0f - m_reloadRemaining / m_weapons[m_selectedWeapon].reloadDuration;
}