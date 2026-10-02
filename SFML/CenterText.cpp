#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode{ { 800u, 600u } }, "Center Text" };
    window.setFramerateLimit(60u);

    auto font = sf::Font{};
    if (!font.openFromFile("tuffy.ttf"))
    {
        std::cerr << "Couldn't load font\n";
        return -1;
    }

    auto rectangle = sf::RectangleShape{ { 300.f, 100.f } };
    rectangle.setOutlineThickness(1.f);
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setPosition({ 200.f, 200.f });
    rectangle.setFillColor(sf::Color::Transparent);

    auto text = sf::Text{ font, "Test 1234" };
    text.setOrigin(text.getGlobalBounds().size / 2.f + text.getLocalBounds().position);
    text.setPosition(rectangle.getPosition() + (rectangle.getSize() / 2.f));

    auto globalBounds = text.getGlobalBounds();
    auto localBounds = text.getLocalBounds();

    std::cout << "(" << globalBounds.position.x << ", " << globalBounds.position.y << ") (" << globalBounds.size.x << ", " << globalBounds.size.y << ")\n";
    std::cout << "(" << localBounds.position.x << ", " << localBounds.position.y << ") (" << localBounds.size.x << ", " << localBounds.size.y << ")\n";

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }
}