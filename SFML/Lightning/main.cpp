#include <SFML/Graphics.hpp>

#include "Lightning.hpp"

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode{ { 800u, 600u } }, "Lightning" };
    window.setFramerateLimit(60u);

    // Initialize lightning class
    auto lightning = Lightning{ 30u, 3u, sf::Color::Green, sf::Color::Blue };
    lightning.setPosition({ 20.f, 20.f });
    lightning.setSize({ 30.f, 600.f });
    lightning.setOrigin({ 0.f, 10.f });
    lightning.rotate(sf::degrees(-10.f));
    lightning.scale({ 0.5f, 0.5f });

    auto paused = false;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
	            window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
                else if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    paused = true;
                }
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->code == sf::Keyboard::Key::Space)
                {
                    paused = false;
                }
            }
        }

        // Give the possibility to freeze the flash
        if (!paused)
        {
            lightning.generate();

            window.clear();
            window.draw(lightning);
            window.display();
        }
    }
}
