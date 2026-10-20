#include "Enemy.h"

#include <algorithm>
#include <cmath>

Enemy::Enemy(float x, float y)
    : m_x(x),
    m_y(y),
    m_radius(0.35f),
    m_health(100.0f),
    m_maxHealth(100.0f),
    m_attackCooldown(0.0f)
{
}

void Enemy::Update(const Map& map, const Player& player, float deltaTime)
{
    if (!IsAlive() || !player.IsAlive())
        return;

    m_attackCooldown = std::max(0.0f, m_attackCooldown - deltaTime);
}

bool Enemy::TryAttack(const Map& map, const Player& player)
{
    if (m_attackCooldown > 0.0f || !HasLineOfSight(map, player))
        return false;

    m_attackCooldown = m_attackInterval;
    return true;
}

bool Enemy::HasLineOfSight(const Map& map, const Player& player) const
{
    const float deltaX = player.GetX() - m_x;
    const float deltaY = player.GetY() - m_y;
    const float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    const int steps = std::max(1, static_cast<int>(distance * 20.0f));

    for (int step = 1; step < steps; ++step)
    {
        const float amount = static_cast<float>(step) / static_cast<float>(steps);
        const int tileX = static_cast<int>(std::floor(m_x + deltaX * amount));
        const int tileY = static_cast<int>(std::floor(m_y + deltaY * amount));
        if (!map.IsWalkable(tileX, tileY))
            return false;
    }

    return true;
}

void Enemy::TakeDamage(float damage)
{
    if (damage > 0.0f)
        m_health = std::max(0.0f, m_health - damage);
}

float Enemy::GetX() const { return m_x; }
float Enemy::GetY() const { return m_y; }
float Enemy::GetRadius() const { return m_radius; }
float Enemy::GetHealth() const { return m_health; }
float Enemy::GetMaxHealth() const { return m_maxHealth; }
bool Enemy::IsAlive() const { return m_health > 0.0f; }
