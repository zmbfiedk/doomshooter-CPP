#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "InputSystem.h"
#include "Map.h"
#include "Player.h"

void RenderMap(const Map& map, const Player& player)
{
    std::cout << "\x1b[2J\x1b[H";
    std::cout << "WASD move | Arrow keys rotate | Space shoot | Esc quit\n\n";

    const int playerX = static_cast<int>(std::floor(player.GetX()));
    const int playerY = static_cast<int>(std::floor(player.GetY()));

    for (int y = 0; y < map.GetHeight(); ++y)
    {
        std::string row = map.GetRow(y);
        if (y == playerY && playerX >= 0 && playerX < map.GetWidth())
            row[playerX] = '@';

        std::cout << row << '\n';
    }

    std::cout << "\n[PLAYER] X: "
        << player.GetX()
        << " Y: "
        << player.GetY()
        << " Rotation: "
        << player.GetRotation()
        << '\n';
}

int main()
{
    const Map map({
        "############",
        "#P.........#",
        "#..####....#",
        "#..........#",
        "#....##....#",
        "#..........#",
        "############"
    });

    InputSystem input;
    Player player(map);

    bool running = true;

    while (running)
    {
        input.Update();

        if (input.IsPressed(InputAction::Quit))
        {
            running = false;
            continue;
        }

        player.Update(input);
        RenderMap(map, player);
    }

    return 0;
}