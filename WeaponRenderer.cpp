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
        sf::Vector2f(0.0f, -140.0f),
        sf::Vector2f(0.0f, -201.0f),
        sf::Vector2f(45.0f, -221.0f)
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
        RenderGlock(window, weaponPosition);
    else if (m_selectedWeapon == 1)
        RenderDoubleBarrel(window, weaponPosition);
    else
        RenderM16(window, weaponPosition);

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

void WeaponRenderer::RenderGlock(sf::RenderWindow& window, sf::Vector2f position) const
{
    sf::ConvexShape slide;
    slide.setPointCount(8);
    slide.setPoint(0, position + sf::Vector2f(-29.0f, -112.0f));
    slide.setPoint(1, position + sf::Vector2f(-22.0f, -121.0f));
    slide.setPoint(2, position + sf::Vector2f(24.0f, -121.0f));
    slide.setPoint(3, position + sf::Vector2f(29.0f, -114.0f));
    slide.setPoint(4, position + sf::Vector2f(26.0f, -91.0f));
    slide.setPoint(5, position + sf::Vector2f(-26.0f, -91.0f));
    slide.setPoint(6, position + sf::Vector2f(-29.0f, -98.0f));
    slide.setPoint(7, position + sf::Vector2f(-29.0f, -105.0f));
    slide.setFillColor(sf::Color(42, 45, 51));
    window.draw(slide);

    sf::RectangleShape barrel(sf::Vector2f(12.0f, 22.0f));
    barrel.setPosition(position + sf::Vector2f(-6.0f, -143.0f));
    barrel.setFillColor(sf::Color(24, 26, 30));
    window.draw(barrel);

    sf::ConvexShape grip;
    grip.setPointCount(6);
    grip.setPoint(0, position + sf::Vector2f(-23.0f, -87.0f));
    grip.setPoint(1, position + sf::Vector2f(21.0f, -87.0f));
    grip.setPoint(2, position + sf::Vector2f(17.0f, -53.0f));
    grip.setPoint(3, position + sf::Vector2f(7.0f, 29.0f));
    grip.setPoint(4, position + sf::Vector2f(-13.0f, 35.0f));
    grip.setPoint(5, position + sf::Vector2f(-25.0f, -50.0f));
    grip.setFillColor(sf::Color(54, 59, 67));
    window.draw(grip);

    sf::RectangleShape triggerGuard(sf::Vector2f(24.0f, 6.0f));
    triggerGuard.setPosition(position + sf::Vector2f(-12.0f, -75.0f));
    triggerGuard.setFillColor(sf::Color(29, 32, 37));
    window.draw(triggerGuard);
}

void WeaponRenderer::RenderDoubleBarrel(sf::RenderWindow& window, sf::Vector2f position) const
{
    sf::ConvexShape stock;
    stock.setPointCount(6);
    stock.setPoint(0, position + sf::Vector2f(-69.0f, -61.0f));
    stock.setPoint(1, position + sf::Vector2f(-24.0f, -73.0f));
    stock.setPoint(2, position + sf::Vector2f(-19.0f, -43.0f));
    stock.setPoint(3, position + sf::Vector2f(-38.0f, -15.0f));
    stock.setPoint(4, position + sf::Vector2f(-68.0f, -22.0f));
    stock.setPoint(5, position + sf::Vector2f(-80.0f, -43.0f));
    stock.setFillColor(sf::Color(102, 63, 36));
    window.draw(stock);

    sf::RectangleShape receiver(sf::Vector2f(52.0f, 42.0f));
    receiver.setPosition(position + sf::Vector2f(-26.0f, -105.0f));
    receiver.setFillColor(sf::Color(48, 48, 48));
    window.draw(receiver);

    sf::RectangleShape upperBarrel(sf::Vector2f(13.0f, 100.0f));
    upperBarrel.setPosition(position + sf::Vector2f(-15.0f, -205.0f));
    upperBarrel.setFillColor(sf::Color(30, 31, 31));
    window.draw(upperBarrel);

    sf::RectangleShape lowerBarrel(sf::Vector2f(13.0f, 100.0f));
    lowerBarrel.setPosition(position + sf::Vector2f(2.0f, -205.0f));
    lowerBarrel.setFillColor(sf::Color(30, 31, 31));
    window.draw(lowerBarrel);

    sf::RectangleShape hinge(sf::Vector2f(58.0f, 8.0f));
    hinge.setPosition(position + sf::Vector2f(-29.0f, -111.0f));
    hinge.setFillColor(sf::Color(118, 78, 42));
    window.draw(hinge);

    sf::RectangleShape triggerGuard(sf::Vector2f(26.0f, 6.0f));
    triggerGuard.setPosition(position + sf::Vector2f(-13.0f, -68.0f));
    triggerGuard.setFillColor(sf::Color(28, 29, 29));
    window.draw(triggerGuard);
}

void WeaponRenderer::RenderM16(sf::RenderWindow& window, sf::Vector2f position) const
{
    sf::RectangleShape stock(sf::Vector2f(70.0f, 28.0f));
    stock.setPosition(position + sf::Vector2f(-83.0f, -63.0f));
    stock.setFillColor(sf::Color(42, 53, 49));
    window.draw(stock);

    sf::RectangleShape receiver(sf::Vector2f(62.0f, 43.0f));
    receiver.setPosition(position + sf::Vector2f(-39.0f, -105.0f));
    receiver.setFillColor(sf::Color(43, 52, 54));
    window.draw(receiver);

    sf::RectangleShape carryHandle(sf::Vector2f(34.0f, 8.0f));
    carryHandle.setPosition(position + sf::Vector2f(-25.0f, -119.0f));
    carryHandle.setFillColor(sf::Color(30, 38, 40));
    window.draw(carryHandle);

    sf::RectangleShape handguard(sf::Vector2f(48.0f, 22.0f));
    handguard.setPosition(position + sf::Vector2f(22.0f, -96.0f));
    handguard.setFillColor(sf::Color(35, 49, 48));
    window.draw(handguard);

    sf::RectangleShape barrel(sf::Vector2f(10.0f, 125.0f));
    barrel.setPosition(position + sf::Vector2f(40.0f, -221.0f));
    barrel.setFillColor(sf::Color(25, 29, 30));
    window.draw(barrel);

    sf::RectangleShape magazine(sf::Vector2f(16.0f, 52.0f));
    magazine.setPosition(position + sf::Vector2f(-4.0f, -63.0f));
    magazine.setFillColor(sf::Color(29, 40, 40));
    window.draw(magazine);

    sf::ConvexShape grip;
    grip.setPointCount(4);
    grip.setPoint(0, position + sf::Vector2f(-32.0f, -62.0f));
    grip.setPoint(1, position + sf::Vector2f(-7.0f, -62.0f));
    grip.setPoint(2, position + sf::Vector2f(-14.0f, 31.0f));
    grip.setPoint(3, position + sf::Vector2f(-35.0f, 21.0f));
    grip.setFillColor(sf::Color(31, 45, 44));
    window.draw(grip);
}
