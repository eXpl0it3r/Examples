#include <SFML/Graphics.hpp>

int main()
{
    // Create window
    auto window = sf::RenderWindow{ sf::VideoMode{ { 800u, 600u } }, "Simple AABB" };
    // Limit frame-rate
    window.setFramerateLimit(60u);

    // Keep track of the frame time
    auto frameTime = sf::Clock{};

    // Big floor
    auto floor = sf::RectangleShape{ { 800.f, 40.f } };
    floor.setPosition({ 0.f, 560.f });
    floor.setFillColor({ 10u, 180u, 30u });

    // Small box
    auto box = sf::RectangleShape{ { 40.f, 40.f } };
    box.setPosition({ 500.f, 480.f });
    box.setFillColor({ 10u, 180u, 30u });

    // Movable player
    auto player = sf::RectangleShape{ { 40.f, 40.f } };
    player.setOrigin({ 20.f, 20.f });
    player.setPosition({ 400.f, 40.f });
    player.setFillColor({ 10u, 30u, 180u });

    // Player speed
    auto speed = sf::Vector2f{ 0.f, 0.f };

    // Gravity value
    constexpr auto Gravity = 980.f;

    // Check if we're touching any floor/box
    auto touching = false;

    while (window.isOpen())
    {
        // Get delta time for frame-rate depended movement
        auto deltaTime = frameTime.restart().asSeconds();

        // Event handling
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
	            window.close();
            }
        }

        // Slow down horizontal speed
        if (speed.x > 6.f)
        {
	        speed.x -= 3.f;
        }
        else if (speed.x < -6.f)
        {
	        speed.x += 3.f;
        }
        else
        {
	        speed.x = 0.f;
        }

        // Adjust vertical speed
        if (touching)
        {
	        speed.y = Gravity;
        }
        else if (speed.y < Gravity)
        {
	        speed.y += 10.f;
        }
        else if(speed.y > Gravity)
        {
	        speed.y = Gravity;
        }

        // Horizontal movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
	        speed.x = 0.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
	        speed.x = -120.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
	        speed.x = 120.f;
        }

        // Jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && touching)
        {
	        speed.y = -300.f;
        }

        // Move the player
        player.setPosition({ player.getPosition().x + speed.x * deltaTime, player.getPosition().y + speed.y * deltaTime });

        // Check collision & position adjustment
        if (floor.getGlobalBounds().findIntersection(player.getGlobalBounds())) // Floor
        {
            player.setPosition({ player.getPosition().x, floor.getPosition().y - player.getOrigin().y });
            touching = true;
        }
        else if (box.getGlobalBounds().findIntersection(player.getGlobalBounds())) // Box
        {
            player.setPosition({ player.getPosition().x, box.getPosition().y - player.getOrigin().y });
            touching = true;
        }
        else // We're not colliding
        {
	        touching = false;
        }

        // Render
        window.clear();
        window.draw(player);
        window.draw(box);
        window.draw(floor);
        window.display();
    }
}
