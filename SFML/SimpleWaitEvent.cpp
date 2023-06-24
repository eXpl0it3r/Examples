#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "Simple WaitEvent"};
    window.setFramerateLimit(144);

    auto rectangle = sf::RectangleShape{{100.f, 100.f}};
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition({200.f, 200.f});

    while (window.isOpen())
    {
        if (rectangle.getFillColor() == sf::Color::Red)
        {
            rectangle.setFillColor(sf::Color::Green);
        }
        else
        {
            rectangle.setFillColor(sf::Color::Red);
        }

        window.clear();
        window.draw(rectangle);
        window.display();

        auto event = sf::Event{};
        if (window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}