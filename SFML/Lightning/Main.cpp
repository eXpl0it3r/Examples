#include <SFML/Graphics.hpp>

#include <ctime>
#include <cstdio> // rand

#include "Lightning.hpp"

int main()
{
    // Initialize random number generator
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Lightning");
    window.setFramerateLimit(60);

    // Initialize lightning class
    Lightning lightning(30, 3, sf::Color::Green, sf::Color::Blue);
    lightning.setPosition(20.f, 20.f);
    lightning.setSize(30.f, 600.f);
    lightning.setOrigin(0.f, 10.f);
    lightning.rotate(-10.f);
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
