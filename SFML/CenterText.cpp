#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 800u, 600u }, "Center Text" };
    window.setFramerateLimit(60u);

    auto font = sf::Font{};
    if (!font.loadFromFile("tuffy.ttf"))
    {
        std::cerr << "Couldn't load font\n";
        return -1;
    }

    auto rectangle = sf::RectangleShape{ { 300.f, 100.f } };
    rectangle.setOutlineThickness(1.f);
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setPosition({ 200.f, 200.f });
    rectangle.setFillColor(sf::Color::Transparent);

    auto text = sf::Text{ "Test 1234", font };
    text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
    text.setPosition(rectangle.getPosition() + (rectangle.getSize() / 2.f));

    auto globalBounds = text.getGlobalBounds();
    auto localBounds = text.getLocalBounds();

    std::cout << "(" << globalBounds.left << ", " << globalBounds.top << ") (" << globalBounds.width << ", " << globalBounds.height << ")\n";
    std::cout << "(" << localBounds.left << ", " << localBounds.top << ") (" << localBounds.width << ", " << localBounds.height << ")\n";

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
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