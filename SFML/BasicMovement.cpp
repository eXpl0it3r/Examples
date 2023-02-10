#include <cmath>
#include <limits>
#include <SFML/Graphics.hpp>

sf::Vector2f normalize(const sf::Vector2f vector)
{
    constexpr auto UnitsInLastPlace = 2;
    const auto Norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));

    // Prevent division by zero
    if (Norm <= std::numeric_limits<float>::epsilon() * Norm * UnitsInLastPlace
        || Norm < std::numeric_limits<float>::min())
    {
        return sf::Vector2f{};
    }

    return vector / Norm;
}

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode{ { 1280u, 720u } }, "Example: Basic Movement" };
    window.setFramerateLimit(60u);

    auto movingRectangle = sf::RectangleShape{ { 64.f, 64.f } };
    movingRectangle.setFillColor({ 100u, 200u, 150u });

    auto directionVector = sf::Vector2f{ 0.f, 0.f };
    auto frameClock = sf::Clock{};

    enum Directions
    {
        LEFT = 0,
        RIGHT = 1,
        UP = 2,
        DOWN = 3,
    };

    auto keyStates = std::vector(4u, false);

    while (window.isOpen())
    {
	    auto velocity = 200.f;
	    auto frameTime = frameClock.restart();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                keyStates[UP] = keyStates[UP] || (event.key.code == sf::Keyboard::Up);
                keyStates[DOWN] = keyStates[DOWN] || (event.key.code == sf::Keyboard::Down);
                keyStates[LEFT] = keyStates[LEFT] || (event.key.code == sf::Keyboard::Left);
                keyStates[RIGHT] = keyStates[RIGHT] || (event.key.code == sf::Keyboard::Right);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    keyStates[UP] = false;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    keyStates[DOWN] = false;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    keyStates[LEFT] = false;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    keyStates[RIGHT] = false;
                }
            }
        }

        if ((keyStates[LEFT] && keyStates[RIGHT]) || (!keyStates[LEFT] && !keyStates[RIGHT]))
        {
            directionVector.x = 0.f;
        }
        else if (keyStates[LEFT])
        {
            directionVector.x = -1.f;
        }
        else if (keyStates[RIGHT])
        {
            directionVector.x = 1.f;
        }

        if ((keyStates[UP] && keyStates[DOWN]) || (!keyStates[UP] && !keyStates[DOWN]))
        {
            directionVector.y = 0.f;
        }
        else if (keyStates[UP])
        {
            directionVector.y = -1.f;
        }
        else if (keyStates[DOWN])
        {
            directionVector.y = 1.f;
        }

        movingRectangle.move(normalize(directionVector) * velocity * frameTime.asSeconds());

        window.clear();
        window.draw(movingRectangle);
        window.display();
    }
}
