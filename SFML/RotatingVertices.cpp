#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

int main()
{
	auto window = sf::RenderWindow{ sf::VideoMode{ { 1280u, 720u } }, "Rotating Vertices" };
	window.setFramerateLimit(60u);

	auto triangle_vertices = std::vector<sf::Vertex>{ 3u };
	triangle_vertices[0].position = { 50.f, 0.f };
	triangle_vertices[0].color = { 110u, 80u, 220u };
	triangle_vertices[1].position = { 0.f, 100.f };
	triangle_vertices[1].color = { 80u, 50u, 100u };
	triangle_vertices[2].position = { 100.f, 100.f };
	triangle_vertices[2].color = { 80u, 50u, 100u };

	auto transformable = sf::Transformable{};
	transformable.setOrigin({ 50.f, 50.f });
	transformable.setPosition({ 1280u / 2.f, 720u / 2.f });

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
				auto deltaPosition = mousePosition - transformable.getPosition();
				auto rotation = sf::radians(std::atan2(deltaPosition.y, deltaPosition.x)) + sf::degrees(90.f);

				transformable.setRotation(rotation);
			}
		}

		window.clear();
		window.draw(triangle_vertices.data(), triangle_vertices.size(), sf::PrimitiveType::Triangles, transformable.getTransform());
		window.display();
	}
}