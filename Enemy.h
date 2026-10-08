#pragma once

#include "Map.h"
#include "Player.h"

class Enemy
{
public:
    Enemy(float x, float y);

    void Update(const Map& map, const Player& player, float deltaTime);
    bool TryAttack(const Map& map, const Player& player);
    void TakeDamage(float damage);

    float GetX() const;
    float GetY() const;
    float GetRadius() const;
    float GetHealth() const;
    float GetMaxHealth() const;
    bool IsAlive() const;

private:
    bool HasLineOfSight(const Map& map, const Player& player) const;

    float m_x;
    float m_y;
    float m_radius;
    float m_health;
    float m_maxHealth;
    float m_attackCooldown;
    const float m_attackInterval = 1.5f;
};
