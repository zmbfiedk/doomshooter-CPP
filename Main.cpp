#include <SFML/Graphics.hpp>

#include "InputSystem.h"
#include "InputAction.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 540), "Doom Shooter");
    window.setVerticalSyncEnabled(true);
    InputSystem input;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        input.Update();
        if (input.IsPressed(InputAction::Quit))
            window.close();

        window.clear(sf::Color(30, 36, 50));
        window.display();
    }

    return 0;
}