#include <cmath>
#include <SFML/Graphics.hpp>

int main()
{
	auto window = sf::RenderWindow{ sf::VideoMode { { 1280u, 720u } }, "Rotating Triangle" };
	window.setFramerateLimit(60u);

	auto triangle = sf::CircleShape{ 50.f, 3u };
	triangle.setFillColor({ 100u, 50u, 200u });

	triangle.setOrigin({ std::round(triangle.getLocalBounds().size.x / 2.f), std::round(triangle.getLocalBounds().size.y / 2.f) });
	triangle.setPosition({ 1280u / 2.f, 720u / 2.f });

	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
			{
				auto mousePosition = window.mapPixelToCoords(mouseMoved->position);
				auto deltaPosition = mousePosition - triangle.getPosition();
				auto rotation = sf::radians(std::atan2(deltaPosition.y, deltaPosition.x)) + sf::degrees(90.f);

				triangle.setRotation(rotation);
			}
		}

		window.clear();
		window.draw(triangle);
		window.display();
	}
}