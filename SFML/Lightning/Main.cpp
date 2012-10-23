#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdio>

#include "Lightning.hpp"

int main()
{
    // Initialize random number generator
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Lightning");
    window.setFramerateLimit(60);

    // Initialize lightning class
    Lightning lightning(30, 3, sf::Color::Green, sf::Color::Blue);
    lightning.setPosition(20.0f, 20.0f);
    lightning.setSize(50.0f, 600.0f);
    lightning.setOrigin(0, 10);
    lightning.rotate(-10);
    lightning.scale(0.5f, 0.5f);

    bool paused = false;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                paused = true;
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                paused = false;
        }

        // Give the possibility to freeze the flash
        if(!paused)
        {
            lightning.generate();

            window.clear();
            window.draw(lightning);
            window.display();
        }
    }
}
