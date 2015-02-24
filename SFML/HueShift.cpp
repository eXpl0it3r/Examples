// Thanks Foaly for the modified and more compact hue shift function

#include <SFML/Graphics.hpp>

#include <cmath> // abs

template <typename T> T clamp(const T& value, const T& low, const T& high)
{
  return value < low ? low : (value > high ? high : value);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hue Shift");
	window.setFramerateLimit(60); // Limit the frame-rate

	sf::RectangleShape rect(sf::Vector2f(350.f, 350.f));
	rect.setPosition(150, 150);

    // Starting color
	float hue = 0.f;

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
                window.close();
		}

        // Calculate the color
        hue += 0.002f;
        if(hue > 1.f)
            hue = 0.f;

        // Convert hue to RGB
        float r = std::abs(3.f - 6.f * hue) - 1.f;
        float g = 2.f - std::abs(2.f - 6.f * hue);
        float b = 2.f - std::abs(4.f - 6.f * hue);

        // Normalize the RGB values with clamp and apply them to the full 255 RGB spectrum
		rect.setFillColor(sf::Color(clamp(r, 0.f, 1.f) * 255, clamp(g, 0.f, 1.f) * 255, clamp(b, 0.f, 1.f) * 255));

		window.clear();
		window.draw(rect);
		window.display();
	}
}
