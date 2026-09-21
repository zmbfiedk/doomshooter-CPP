#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 540), "Doom Shooter");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 36, 50));
        window.display();
    }

    return 0;
}