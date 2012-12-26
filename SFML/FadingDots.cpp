#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <list>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Fading Dots");
    window.setFramerateLimit(60);

    sf::Vector2f old_pos(0.f, 0.f);
    const int STEP = 1;

    std::list<sf::CircleShape> points;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Check if the mouse has moved
        sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if(pos != old_pos)
        {
            // Create and add a new circle to the points list.
            sf::CircleShape cs;
            cs.setRadius(10.f);
            cs.setPosition(pos);
            cs.setFillColor(sf::Color::Red);
            points.push_back(cs);

            old_pos = pos;
        }

        window.clear();

        for(auto it = points.begin(); it != points.end(); ++it)
        {
            window.draw(*it);
            if(it->getFillColor().a-STEP < 0) // When the transparency falls below zero (= invisible) then erase the dot.
                it = points.erase(it);
            else // Otherwise draw it with a increasing green touch (turns yellowish).
                it->setFillColor(sf::Color(255, it->getFillColor().g+STEP, 0, it->getFillColor().a-STEP));
        }

        window.display();
    }
}
