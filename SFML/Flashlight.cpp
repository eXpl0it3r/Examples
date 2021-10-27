#include <SFML/Graphics.hpp>

class Application
{
public:
    Application() :
        m_window{ { 300, 300 }, "Flashlight!" },
        m_rectangle{ { 100.f, 100.f } },
        m_position{ 0.f, 0.f }
    {
        m_window.setFramerateLimit(60);
        m_window.setMouseCursorVisible(false);

        m_layer.create(300, 300);
        m_flashlightTexture.create(60, 60);

        // We want to have semi-transparent edges.
        generateSpot();

        m_flashlight.setTexture(m_flashlightTexture.getTexture(), true);
        m_flashlight.setPosition({ 150.f, 150.f });
        m_flashlight.setOrigin({ 30.f, 30.f });

        m_rectangle.setFillColor(sf::Color::Red);
        m_rectangle.setPosition({ 100.f, 100.f });

        m_sprite.setTexture(m_layer.getTexture());
    }

    void generateSpot()
    {
        m_flashlightTexture.clear();

        // Draw 6 circles with increasing transparency
        for (auto i = 0; i < 6; ++i)
        {
	        const auto index = static_cast<float>(i);

            auto temp = sf::CircleShape{ 30.f - (index * 2.f) };
            temp.setOrigin({ 30.f - (index * 2.f), 30.f - (index * 2.f) });
            temp.setFillColor({ 255, 255, 255, static_cast<sf::Uint8>(61 - (i * 10)) });
            temp.setPosition({ 30.f, 30.f });

            m_flashlightTexture.draw(temp, sf::BlendNone);
        }

        m_flashlightTexture.display();
    }

    void run()
    {
        while (m_window.isOpen())
        {
            for (auto event = sf::Event{}; m_window.pollEvent(event);)
            {
                if (event.type == sf::Event::Closed)
                {
	                m_window.close();
                }
            }

            // Update the position of the 'flashlight' to the current mouse position
            m_position = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
            m_flashlight.setPosition(m_position);

            // Stance-out the 'flashlight' circle
            m_layer.clear();
            m_layer.draw(m_flashlight, sf::BlendNone);
            m_layer.display();

            m_window.clear(sf::Color::Blue);

            // Draw the layer sprite on top of the 'scene'
            m_window.draw(m_rectangle);
            m_window.draw(m_sprite);

            m_window.display();
        }
    }

private:
    sf::RenderWindow m_window;
    sf::RenderTexture m_flashlightTexture;
    sf::RenderTexture m_layer;
    sf::RectangleShape m_rectangle;
    sf::Sprite m_flashlight;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
};

int main()
{
    auto app = Application{};
    app.run();
}
