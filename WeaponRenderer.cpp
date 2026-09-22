#include "WeaponRenderer.h"

#include <algorithm>
#include <stdexcept>

WeaponRenderer::WeaponRenderer(
    unsigned int viewportWidth,
    unsigned int viewportHeight)
    : m_viewportWidth(viewportWidth),
    m_viewportHeight(viewportHeight),
    m_selectedWeapon(0),
    m_muzzleOffsets({
        sf::Vector2f(0.0f, -108.0f),
        sf::Vector2f(0.0f, -118.0f),
        sf::Vector2f(0.0f, -125.0f)
    }),
    m_muzzleFlashRemaining(0.0f)
{
    const std::array<std::string, WeaponCount> assetPaths = {
        "assets/gun_pistol.png",
        "assets/gun_shotgun.png",
        "assets/gun_rifle.png"
    };

    for (std::size_t index = 0; index < WeaponCount; ++index)
    {
        if (!m_textures[index].loadFromFile(assetPaths[index]))
            throw std::runtime_error("Could not load " + assetPaths[index]);

        m_sprites[index].setTexture(m_textures[index]);
        const sf::FloatRect bounds = m_sprites[index].getLocalBounds();
        m_sprites[index].setOrigin(
            bounds.left + bounds.width / 2.0f,
            bounds.top + bounds.height / 2.0f);
    }
}

void WeaponRenderer::SelectWeapon(std::size_t weaponIndex)
{
    if (weaponIndex < WeaponCount)
        m_selectedWeapon = weaponIndex;
}

void WeaponRenderer::TriggerMuzzleFlash()
{
    m_muzzleFlashRemaining = 0.06f;
}

void WeaponRenderer::Update(float deltaTime)
{
    m_muzzleFlashRemaining = std::max(0.0f, m_muzzleFlashRemaining - deltaTime);
}

void WeaponRenderer::Render(sf::RenderWindow& window)
{
    sf::Sprite& sprite = m_sprites[m_selectedWeapon];
    const sf::Vector2f weaponPosition(
        static_cast<float>(m_viewportWidth) / 2.0f,
        static_cast<float>(m_viewportHeight) - 105.0f);
    sprite.setPosition(weaponPosition);

    window.draw(sprite);

    if (m_muzzleFlashRemaining <= 0.0f)
        return;

    const sf::Vector2f muzzlePosition = weaponPosition + m_muzzleOffsets[m_selectedWeapon];

    sf::CircleShape glow(10.0f);
    glow.setOrigin(10.0f, 10.0f);
    glow.setPosition(muzzlePosition);
    glow.setFillColor(sf::Color(255, 220, 80, 220));
    window.draw(glow);

    sf::RectangleShape horizontal(sf::Vector2f(34.0f, 4.0f));
    horizontal.setOrigin(17.0f, 2.0f);
    horizontal.setPosition(muzzlePosition);
    horizontal.setFillColor(sf::Color(255, 245, 180, 220));
    window.draw(horizontal);

    sf::RectangleShape vertical(sf::Vector2f(4.0f, 34.0f));
    vertical.setOrigin(2.0f, 17.0f);
    vertical.setPosition(muzzlePosition);
    vertical.setFillColor(sf::Color(255, 245, 180, 220));
    window.draw(vertical);
}

