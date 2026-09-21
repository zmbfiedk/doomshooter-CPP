#include "WeaponRenderer.h"

#include <stdexcept>

WeaponRenderer::WeaponRenderer(
    unsigned int viewportWidth,
    unsigned int viewportHeight)
    : m_viewportWidth(viewportWidth),
    m_viewportHeight(viewportHeight),
    m_selectedWeapon(0)
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

void WeaponRenderer::Render(sf::RenderWindow& window)
{
    sf::Sprite& sprite = m_sprites[m_selectedWeapon];
    sprite.setPosition(
        static_cast<float>(m_viewportWidth) / 2.0f,
        static_cast<float>(m_viewportHeight) - 105.0f);
    window.draw(sprite);
}
