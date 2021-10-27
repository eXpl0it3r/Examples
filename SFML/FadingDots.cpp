#include <SFML/Graphics.hpp>

#include <list>

int main()
{
    auto window = sf::RenderWindow{ { 500, 500 }, "Fading Dots" };
    window.setFramerateLimit(60);

    auto old_position = sf::Vector2f{ 0.f, 0.f };
    const auto STEP = 1;

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
        if (position != old_position)
        {
            // Create and add a new circle to the points list.
            auto circle_shape = sf::CircleShape{ 10.f };
            circle_shape.setRadius(10.f);
            circle_shape.setPosition(position);
            circle_shape.setFillColor(sf::Color::Red);
            points.push_back(circle_shape);

            old_position = position;
        }

        window.clear();

        for (auto it = points.begin(); it != points.end(); ++it)
        {
            window.draw(*it);

            if (it->getFillColor().a - STEP < 0) // When the transparency falls below zero (= invisible) then erase the dot.
            {
	            it = points.erase(it);
            }
            else // Otherwise draw it with a increasing green touch (turns yellowish).
            {
                it->setFillColor({ 255, static_cast<sf::Uint8>(it->getFillColor().g + STEP), 0, static_cast<sf::Uint8>(it->getFillColor().a - STEP) });
            }
        }

        window.display();
    }
}
