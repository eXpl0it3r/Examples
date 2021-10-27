#include <cmath>
#include <limits>
#include <SFML/Graphics.hpp>

sf::Vector2f normalize(const sf::Vector2f vector)
{
    constexpr auto units_in_last_place = 2;
    const auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));

    // Prevent division by zero
    if (norm <= std::numeric_limits<float>::epsilon() * norm * units_in_last_place
        || norm < std::numeric_limits<float>::min())
    {
        return sf::Vector2f{};
    }

    return vector / norm;
}

int main()
{
    auto window = sf::RenderWindow{ { 1280u, 720u }, "Example: Basic Movement" };
    window.setFramerateLimit(60);

    auto moving_rectangle = sf::RectangleShape{ { 64.f, 64.f } };
    moving_rectangle.setFillColor({ 100, 200, 150 });

    auto direction_vector = sf::Vector2f{ 0.f, 0.f };
    auto frame_clock = sf::Clock{};

    enum Directions
    {
        LEFT = 0,
        RIGHT = 1,
        UP = 2,
        DOWN = 3,
    };

    auto key_states = std::vector(4, false);

    while (window.isOpen())
    {
	    auto velocity = 200.f;
	    auto frame_time = frame_clock.restart();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                key_states[UP] = key_states[UP] || (event.key.code == sf::Keyboard::Up);
                key_states[DOWN] = key_states[DOWN] || (event.key.code == sf::Keyboard::Down);
                key_states[LEFT] = key_states[LEFT] || (event.key.code == sf::Keyboard::Left);
                key_states[RIGHT] = key_states[RIGHT] || (event.key.code == sf::Keyboard::Right);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    key_states[UP] = false;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    key_states[DOWN] = false;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    key_states[LEFT] = false;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    key_states[RIGHT] = false;
                }
            }
        }

        if ((key_states[LEFT] && key_states[RIGHT]) || (!key_states[LEFT] && !key_states[RIGHT]))
        {
            direction_vector.x = 0.f;
        }
        else if (key_states[LEFT])
        {
            direction_vector.x = -1.f;
        }
        else if (key_states[RIGHT])
        {
            direction_vector.x = 1.f;
        }

        if ((key_states[UP] && key_states[DOWN]) || (!key_states[UP] && !key_states[DOWN]))
        {
            direction_vector.y = 0.f;
        }
        else if (key_states[UP])
        {
            direction_vector.y = -1.f;
        }
        else if (key_states[DOWN])
        {
            direction_vector.y = 1.f;
        }

        moving_rectangle.move(normalize(direction_vector) * velocity * frame_time.asSeconds());

        window.clear();
        window.draw(moving_rectangle);
        window.display();
    }
}
