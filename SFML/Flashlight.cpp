#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Application
{
public:
    Application() :
        m_window(sf::VideoMode(300, 300), "Flashlight!"),
        m_layer(),
        m_rect(sf::Vector2f(100.f, 100.f)),
        m_pos(0.f, 0.f)
    {
        m_window.setFramerateLimit(60);
        m_window.setMouseCursorVisible(false);

        m_layer.create(300, 300);
        m_flashlightTexture.create(60, 60);

        // We want to have semi-transparent edges.
        generateSpot();

        m_flashlight.setTexture(m_flashlightTexture.getTexture(), true);
        m_flashlight.setPosition(150.f, 150.f);
        m_flashlight.setOrigin(30.f, 30.f);

        m_rect.setFillColor(sf::Color::Red);
        m_rect.setPosition(100.f, 100.f);

        m_sprite.setTexture(m_layer.getTexture());
    }

    void generateSpot()
    {
        m_flashlightTexture.clear();

        // Draw 6 circles with increasing transparency
        for(unsigned int i = 0; i < 6; ++i)
        {
            sf::CircleShape temp(30.f-(i*2.f));
            temp.setOrigin(sf::Vector2f(30.f-(i*2.f), 30.f-(i*2.f)));
            temp.setFillColor(sf::Color(255, 255, 255, 61-(i*10)));
            temp.setPosition(sf::Vector2f(30.f, 30.f));

            m_flashlightTexture.draw(temp, sf::BlendNone);
        }

        m_flashlightTexture.display();
    }

    void run()
    {
        while(m_window.isOpen())
        {
            sf::Event event;
            while(m_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    m_window.close();
            }

            // Update the position of the 'flashlight' to the current mouse position
            m_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
            m_flashlight.setPosition(m_pos);

            // Stance-out the 'flashlight' circle
            m_layer.clear();
            m_layer.draw(m_flashlight, sf::BlendNone);
            m_layer.display();

            m_window.clear(sf::Color::Blue);

            // Draw the layer sprite on top of the 'scene'
            m_window.draw(m_rect);
            m_window.draw(m_sprite);

            m_window.display();
        }
    }

private:
    sf::RenderWindow m_window;
    sf::RenderTexture m_flashlightTexture;
    sf::RenderTexture m_layer;
    sf::RectangleShape m_rect;
    sf::Sprite m_flashlight;
    sf::Sprite m_sprite;
    sf::Vector2f m_pos;
};

int main()
{
    Application app;
    app.run();
}
