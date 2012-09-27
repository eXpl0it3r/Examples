#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow Screen (sf::VideoMode (800, 600, 32), "Game", sf::Style::Close);
	Screen.setFramerateLimit(60);

	sf::RectangleShape rect(sf::Vector2f(350.f, 350.f));
	rect.setPosition(150, 150);

	int dr = 0;
	int dg = 0;
	int db = 0;

	sf::Uint8 r = 255, g = 0,  b = 0;

	while (Screen.isOpen())
	{
		sf::Event Event;
		while (Screen.pollEvent (Event))
		{
			if (Event.type == sf::Event::Closed)
				Screen.close();
		}

		r += dr;
		g += dg;
		b += db;

		if(r == 255 && g == 0 && b == 0)
		{
			dr = 0; dg = 1; db = 0;
		}

		if(r == 255 && g == 255 && b == 0)
		{
			dr = -1; dg = 0; db = 0;
		}

		if(r == 0 && g == 255 && b == 0)
		{
			dr = 0; dg = 0; db = 1;
		}

		if(r == 0 && g == 255 && b == 255)
		{
			dr = 0; dg = -1; db = 0;
		}

		if(r == 0 && g == 0 && b == 255)
		{
			dr = 1; dg = 0; db = 0;
		}

		if(r == 255 && g == 0 && b == 255)
		{
			dr = 0; dg = 0; db = -1;
		}

		rect.setFillColor(sf::Color(r, g, b));

		Screen.clear();
		Screen.draw(rect);
		Screen.display();
	}

	return 0;
}