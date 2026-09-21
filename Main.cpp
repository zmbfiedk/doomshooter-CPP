#include <algorithm>

#include <SFML/Graphics.hpp>

#include "InputSystem.h"
#include "InputAction.h"
#include "Map.h"
#include "Player.h"
#include "Raycaster.h"
#include "Renderer.h"

int main()
{
    const Map map({
        "########################",
        "#P.....................#",
        "#..######..............#",
        "#......................#",
        "#........####..........#",
        "#......................#",
        "#......######..........#",
        "#......................#",
        "#..........####........#",
        "#......................#",
        "#..............######..#",
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
        const std::vector<RayHit> hits = raycaster.CastView(map, player, 960);

        renderer.Render(window, hits);
        window.display();
    }

    return 0;
}