#include <algorithm>

#include <SFML/Graphics.hpp>

#include "InputSystem.h"
#include "InputAction.h"
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"
#include "Renderer.h"
#include "ShootingSystem.h"
#include "WeaponRenderer.h"

int main()
{
    const Map map({
        "########################",
        "#P.....................#",
        "#..######..............#",
        "#......................#",
        "#........####..........#",
        "#......................#",
        "#.......#####..........#",
        "#....#.................#",
        "#....#.....####........#",
        "#....#.................#",
        "#...###........######..#",
        "#......................#",
        "#......................#",
        "########################"
    });

    sf::RenderWindow window(sf::VideoMode(960, 540), "Doom Shooter");
    window.setVerticalSyncEnabled(true);
    InputSystem input;
    Player player(map);
    Raycaster raycaster;
    Renderer renderer(960, 540);
    ShootingSystem shootingSystem;
    WeaponRenderer weaponRenderer(960, 540);
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
        const ShootingResult shootingResult = shootingSystem.Update(
            map,
            player,
            raycaster,
            input.IsPressed(InputAction::Shoot),
            deltaTime);
        if (shootingResult.fired)
            weaponRenderer.TriggerMuzzleFlash();
        weaponRenderer.Update(deltaTime);

        const std::vector<RayHit> hits = raycaster.CastView(map, player, 960);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            weaponRenderer.SelectWeapon(0);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            weaponRenderer.SelectWeapon(1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            weaponRenderer.SelectWeapon(2);

        renderer.Render(window, hits);
        weaponRenderer.Render(window);
        window.display();
    }

    return 0;
}