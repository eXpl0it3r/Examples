#include <cmath>
#include <SFML/Graphics.hpp>

static constexpr auto PI = 3.14159265359f;

static constexpr float to_degree(const float radian)
{
	return radian * (180.f / PI);
}

int main()
{
	auto window = sf::RenderWindow{ { 1280u, 720u }, "Rotating Triangle" };
	window.setFramerateLimit(60u);

	auto triangle = sf::CircleShape{ 50.f, 3u };
	triangle.setFillColor({ 100u, 50u, 200u });

	triangle.setOrigin({ std::round(triangle.getLocalBounds().width / 2.f), std::round(triangle.getLocalBounds().height / 2.f) });
	triangle.setPosition({ 1280u / 2.f, 720u / 2.f });

	while (window.isOpen())
	{
		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				auto mousePosition = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				auto deltaPosition = sf::Vector2f{ mousePosition.x - triangle.getPosition().x, mousePosition.y - triangle.getPosition().y };
				auto rotation = to_degree(atan2(deltaPosition.y, deltaPosition.x)) + 90.f;

				triangle.setRotation(rotation);
			}
		}

		window.clear();
		window.draw(triangle);
		window.display();
	}
}