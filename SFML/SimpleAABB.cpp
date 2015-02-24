#include <SFML/Graphics.hpp>

int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
    // Limit frame-rate
    window.setFramerateLimit(60);

    // Keep track of the frametime
    sf::Clock frametime;

    // Big floor
    sf::RectangleShape floor(sf::Vector2f(800.f, 40.f));
    floor.setPosition(0.f, 560.f);
    floor.setFillColor(sf::Color(10, 180, 30));

    // Small box
    sf::RectangleShape box(sf::Vector2f(40.f, 40.f));
    box.setPosition(500.f, 480.f);
    box.setFillColor(sf::Color(10, 180, 30));

    // Movable player
    sf::RectangleShape player(sf::Vector2f(40.f, 40.f));
    player.setOrigin(20.f, 20.f);
    player.setPosition(400.f, 40.f);
    player.setFillColor(sf::Color(10, 30, 180));

    // Player speed
    sf::Vector2f speed(0.f, 0.f);

    // Gravity value
    const float gravity = 980.f;

    // Check if we're touching any floor/box
    bool touching = false;

    while(window.isOpen())
    {
        // Get delta time for frame-rate depended movement
        float dt = frametime.restart().asSeconds();

        // Event handling
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Slow down horizontal speed
        if(speed.x > 6.f)
            speed.x -= 3.f;
        else if(speed.x < -6.f)
            speed.x += 3.f;
        else
            speed.x = 0.f;

        // Adjust vertical speed
        if(touching)
            speed.y = gravity;
        else if(speed.y < gravity)
            speed.y += 10.f;
        else if(speed.y > gravity)
            speed.y = gravity;

        // Horizontal movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            speed.x = 0.f;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            speed.x = -120.f;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            speed.x = 120.f;

        // Jumping
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && touching)
            speed.y = -300.f;

        // Move the player
        player.setPosition(player.getPosition().x + speed.x * dt, player.getPosition().y + speed.y * dt);

        // Check collision & position adjustment
        if(floor.getGlobalBounds().intersects(player.getGlobalBounds())) // Floor
        {
            player.setPosition(player.getPosition().x, floor.getPosition().y-player.getOrigin().y);
            touching = true;
        }
        else if(box.getGlobalBounds().intersects(player.getGlobalBounds())) // Box
        {
            player.setPosition(player.getPosition().x, box.getPosition().y-player.getOrigin().y);
            touching = true;
        }
        else // We're not colliding
            touching = false;

        // Render
        window.clear();
        window.draw(player);
        window.draw(box);
        window.draw(floor);
        window.display();
    }
}
