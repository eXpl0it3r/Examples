#include <SFML/Graphics.hpp>

#include <cstdint>
#include <list>

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode{ { 500u, 500u } }, "Fading Dots" };
    window.setFramerateLimit(60u);

    auto oldPosition = sf::Vector2f{ 0.f, 0.f };
    constexpr auto Step = 1;

    auto points = std::list<sf::CircleShape>{};

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
	            window.close();
            }
        }

        // Check if the mouse has moved
        auto position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (position != oldPosition)
        {
            // Create and add a new circle to the points list.
            auto circleShape = sf::CircleShape{ 10.f };
            circleShape.setRadius(10.f);
            circleShape.setPosition(position);
            circleShape.setFillColor(sf::Color::Red);
            points.push_back(circleShape);

            oldPosition = position;
        }

        window.clear();

        for (auto it = points.begin(); it != points.end(); ++it)
        {
            window.draw(*it);

            if (it->getFillColor().a - Step < 0) // When the transparency falls below zero (= invisible) then erase the dot.
            {
	            it = points.erase(it);
            }
            else // Otherwise draw it with a increasing green touch (turns yellowish).
            {
                it->setFillColor({ 255u, static_cast<std::uint8_t>(it->getFillColor().g + Step), 0u, static_cast<std::uint8_t>(it->getFillColor().a - Step) });
            }
        }

        window.display();
    }
}
