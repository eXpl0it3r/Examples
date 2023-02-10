// Thanks Foaly for the modified and more compact hue shift function

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode{ { 800u, 600u } }, "Hue Shift" };
    window.setFramerateLimit(60u); // Limit the frame-rate

    auto rectangle = sf::RectangleShape{ { 350.f, 350.f } };
    rectangle.setPosition({ 150.f, 150.f });

    // Starting color
    auto hue = 0.f;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
	            window.close();
            }
        }

        // Calculate the color
        hue += 0.002f;
        if (hue > 1.f)
        {
	        hue = 0.f;
        }

        // Convert hue to RGB
        auto r = std::abs(3.f - 6.f * hue) - 1.f;
        auto g = 2.f - std::abs(2.f - 6.f * hue);
        auto b = 2.f - std::abs(4.f - 6.f * hue);

        // Normalize the RGB values with clamp and apply them to the full 255 RGB spectrum
        rectangle.setFillColor({
            static_cast<std::uint8_t>(std::clamp(r, 0.f, 1.f) * 255u),
        	static_cast<std::uint8_t>(std::clamp(g, 0.f, 1.f) * 255u),
        	static_cast<std::uint8_t>(std::clamp(b, 0.f, 1.f) * 255u)
        });

        window.clear();
        window.draw(rectangle);
        window.display();
    }
}
