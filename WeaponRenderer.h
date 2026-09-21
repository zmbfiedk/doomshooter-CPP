#pragma once

#include <array>
#include <string>

#include <SFML/Graphics.hpp>

class WeaponRenderer
{
public:
    WeaponRenderer(unsigned int viewportWidth, unsigned int viewportHeight);

    void SelectWeapon(std::size_t weaponIndex);
    void Render(sf::RenderWindow& window);

private:
    static constexpr std::size_t WeaponCount = 3;

    std::array<sf::Texture, WeaponCount> m_textures;
    std::array<sf::Sprite, WeaponCount> m_sprites;
    unsigned int m_viewportWidth;
    unsigned int m_viewportHeight;
    std::size_t m_selectedWeapon;
};
