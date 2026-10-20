#include "HudRenderer.h"

#include <algorithm>

HudRenderer::HudRenderer(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
}

void HudRenderer::Render(
    sf::RenderWindow& window,
    const Player& player,
    const ShootingSystem& shooting) const
{
    const float healthRatio = player.GetHealth() / player.GetMaxHealth();
    sf::RectangleShape healthBack(sf::Vector2f(220.0f, 22.0f));
    healthBack.setPosition(20.0f, 20.0f);
    healthBack.setFillColor(sf::Color(55, 15, 20, 220));
    window.draw(healthBack);

    sf::RectangleShape health(sf::Vector2f(216.0f * std::max(0.0f, healthRatio), 18.0f));
    health.setPosition(22.0f, 22.0f);
    health.setFillColor(sf::Color(210, 35, 40));
    window.draw(health);

    const float ammoRatio = static_cast<float>(shooting.GetMagazineAmmo())
        / static_cast<float>(shooting.GetMagazineSize());
    sf::RectangleShape ammoBack(sf::Vector2f(220.0f, 16.0f));
    ammoBack.setPosition(
        static_cast<float>(m_width) - 240.0f,
        static_cast<float>(m_height) - 42.0f);
    ammoBack.setFillColor(sf::Color(25, 25, 25, 220));
    window.draw(ammoBack);

    sf::RectangleShape ammo(sf::Vector2f(216.0f * ammoRatio, 12.0f));
    ammo.setPosition(
        static_cast<float>(m_width) - 238.0f,
        static_cast<float>(m_height) - 40.0f);
    ammo.setFillColor(sf::Color(240, 190, 50));
    window.draw(ammo);

    sf::CircleShape crosshair(3.0f);
    crosshair.setOrigin(3.0f, 3.0f);
    crosshair.setPosition(
        static_cast<float>(m_width) * 0.5f,
        static_cast<float>(m_height) * 0.5f);
    crosshair.setFillColor(sf::Color::White);
    window.draw(crosshair);

    if (shooting.IsReloading())
    {
        sf::RectangleShape reload(sf::Vector2f(
            180.0f * shooting.GetReloadProgress(), 8.0f));
        reload.setPosition(
            (static_cast<float>(m_width) - 180.0f) * 0.5f,
            static_cast<float>(m_height) - 70.0f);
        reload.setFillColor(sf::Color(80, 180, 240));
        window.draw(reload);
    }

    if (!player.IsAlive())
    {
        sf::RectangleShape gameOver(sf::Vector2f(
            static_cast<float>(m_width), static_cast<float>(m_height)));
        gameOver.setFillColor(sf::Color(100, 0, 0, 100));
        window.draw(gameOver);
    }
}
