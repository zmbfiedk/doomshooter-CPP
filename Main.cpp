#include <algorithm>

#include <SFML/Graphics.hpp>

#include "InputSystem.h"
#include "InputAction.h"
#include "Enemy.h"
#include "HudRenderer.h"
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"
#include "Renderer.h"
#include "ShootingSystem.h"
#include "WeaponRenderer.h"

int main()
{
    const Map map({
        "########################.",
        "#P.....................#.",
        "#..######..............#.",
        "#......................#.",
        "#........####..........#.",
        "#......................#.",
        "#.......#####..........#.",
        "#....#.................#.",
        "#....#.....####........#.",
        "#....#.................#.",
        "#...###........######...#",
        "#......................#.",
        "#......................#.",
        "########################."
    });

    sf::RenderWindow window(sf::VideoMode(960, 540), "Doom Shooter");
    window.setVerticalSyncEnabled(true);
    InputSystem input;
    Player player(map);
    Enemy enemy(10.5f, 1.5f);
    Raycaster raycaster;
    Renderer renderer(960, 540);
    ShootingSystem shootingSystem;
    WeaponRenderer weaponRenderer(960, 540);
    HudRenderer hudRenderer(960, 540);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const float deltaTime = std::min(clock.restart().asSeconds(), 0.1f);
        input.Update();
        if (input.IsPressed(InputAction::Quit))
            window.close();

        player.Update(input, deltaTime);
        enemy.Update(map, player, deltaTime);
        if (enemy.TryAttack(map, player))
            player.TakeDamage(10.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            shootingSystem.SelectWeapon(0);
            weaponRenderer.SelectWeapon(0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            shootingSystem.SelectWeapon(1);
            weaponRenderer.SelectWeapon(1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            shootingSystem.SelectWeapon(2);
            weaponRenderer.SelectWeapon(2);
        }

        const ShootingResult shootingResult = shootingSystem.Update(
            map,
            player,
            raycaster,
            enemy,
            input.IsPressed(InputAction::Shoot),
            input.IsPressed(InputAction::Reload),
            deltaTime);
        if (shootingResult.fired)
            weaponRenderer.TriggerMuzzleFlash();
        weaponRenderer.Update(deltaTime);

        const std::vector<RayHit> hits = raycaster.CastView(map, player, 960);

        renderer.Render(window, hits);
        renderer.RenderEnemy(window, player, enemy, hits);
        weaponRenderer.Render(window);
        hudRenderer.Render(window, player, shootingSystem);
        window.display();
    }

    return 0;
}