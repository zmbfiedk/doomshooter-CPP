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
        sf::Vector2f(0.0f, -135.0f),
        sf::Vector2f(0.0f, -143.0f),
        sf::Vector2f(22.0f, -153.0f)
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

    if (m_selectedWeapon == 0)
        RenderPistol(window, weaponPosition);
    else if (m_selectedWeapon == 1)
        RenderShotgun(window, weaponPosition);
    else
        RenderRifle(window, weaponPosition);

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

void WeaponRenderer::RenderPistol(sf::RenderWindow& window, sf::Vector2f position) const
{
    sf::RectangleShape slide(sf::Vector2f(54.0f, 35.0f));
    slide.setPosition(position + sf::Vector2f(-27.0f, -105.0f));
    slide.setFillColor(sf::Color(45, 49, 58));
    window.draw(slide);

    sf::RectangleShape barrel(sf::Vector2f(14.0f, 35.0f));
    barrel.setPosition(position + sf::Vector2f(-7.0f, -140.0f));
    barrel.setFillColor(sf::Color(28, 31, 38));
    window.draw(barrel);

    sf::ConvexShape grip;
    grip.setPointCount(4);
    grip.setPoint(0, position + sf::Vector2f(-22.0f, -70.0f));
    grip.setPoint(1, position + sf::Vector2f(22.0f, -70.0f));
    grip.setPoint(2, position + sf::Vector2f(14.0f, 28.0f));
    grip.setPoint(3, position + sf::Vector2f(-14.0f, 28.0f));
    grip.setFillColor(sf::Color(55, 60, 70));
    window.draw(grip);

    sf::RectangleShape triggerGuard(sf::Vector2f(22.0f, 5.0f));
    triggerGuard.setPosition(position + sf::Vector2f(-11.0f, -68.0f));
    triggerGuard.setFillColor(sf::Color(220, 85, 55));
    window.draw(triggerGuard);
}

void WeaponRenderer::RenderShotgun(sf::RenderWindow& window, sf::Vector2f position) const
{
    sf::RectangleShape stock(sf::Vector2f(48.0f, 38.0f));
    stock.setPosition(position + sf::Vector2f(-58.0f, -57.0f));
    stock.setFillColor(sf::Color(82, 52, 35));
    window.draw(stock);

    sf::RectangleShape receiver(sf::Vector2f(58.0f, 38.0f));
    receiver.setPosition(position + sf::Vector2f(-29.0f, -96.0f));
    receiver.setFillColor(sf::Color(55, 58, 62));
    window.draw(receiver);

    sf::RectangleShape upperBarrel(sf::Vector2f(12.0f, 105.0f));
    upperBarrel.setPosition(position + sf::Vector2f(-15.0f, -201.0f));
    upperBarrel.setFillColor(sf::Color(35, 38, 42));
    window.draw(upperBarrel);

    sf::RectangleShape lowerBarrel(sf::Vector2f(12.0f, 105.0f));
    lowerBarrel.setPosition(position + sf::Vector2f(3.0f, -201.0f));
    lowerBarrel.setFillColor(sf::Color(35, 38, 42));
    window.draw(lowerBarrel);

    sf::RectangleShape foregrip(sf::Vector2f(48.0f, 18.0f));
    foregrip.setPosition(position + sf::Vector2f(-24.0f, -117.0f));
    foregrip.setFillColor(sf::Color(112, 70, 40));
    window.draw(foregrip);
}

void WeaponRenderer::RenderRifle(sf::RenderWindow& window, sf::Vector2f position) const
{
    sf::RectangleShape stock(sf::Vector2f(65.0f, 30.0f));
    stock.setPosition(position + sf::Vector2f(-78.0f, -55.0f));
    stock.setFillColor(sf::Color(37, 64, 62));
    window.draw(stock);

    sf::RectangleShape receiver(sf::Vector2f(58.0f, 43.0f));
    receiver.setPosition(position + sf::Vector2f(-35.0f, -97.0f));
    receiver.setFillColor(sf::Color(42, 57, 63));
    window.draw(receiver);

    sf::RectangleShape handguard(sf::Vector2f(42.0f, 20.0f));
    handguard.setPosition(position + sf::Vector2f(23.0f, -86.0f));
    handguard.setFillColor(sf::Color(35, 48, 52));
    window.draw(handguard);

    sf::RectangleShape barrel(sf::Vector2f(10.0f, 120.0f));
    barrel.setPosition(position + sf::Vector2f(39.0f, -206.0f));
    barrel.setFillColor(sf::Color(25, 31, 35));
    window.draw(barrel);

    sf::ConvexShape grip;
    grip.setPointCount(4);
    grip.setPoint(0, position + sf::Vector2f(-25.0f, -55.0f));
    grip.setPoint(1, position + sf::Vector2f(2.0f, -55.0f));
    grip.setPoint(2, position + sf::Vector2f(-7.0f, 28.0f));
    grip.setPoint(3, position + sf::Vector2f(-28.0f, 18.0f));
    grip.setFillColor(sf::Color(34, 48, 50));
    window.draw(grip);
}
