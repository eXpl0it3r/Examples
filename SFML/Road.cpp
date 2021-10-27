// Warning: This code isn't nice at all, so don't even think about using it in production code. ;-)

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 1024, 768 }, "Road" };
    window.setFramerateLimit(60);

    auto grass = sf::RectangleShape{ { 262.f, 768.f } };
    grass.setFillColor({ 0, 100, 0 });

    auto road = sf::RectangleShape{ { 500.f, 768.f } };
    road.setFillColor({ 50, 50, 50 });
    road.setPosition({ 262.f, 0.f });

    const auto HEIGHT = 70.f;
    const auto STRIPES_COUNT = 7U;

    auto greyLight = sf::RectangleShape{ { 1024.f, HEIGHT } };
    greyLight.setFillColor({ 50, 50, 50, 20 });

    auto greyDark = sf::RectangleShape{ { 1024.f, HEIGHT } };
    greyDark.setFillColor({ 50, 50, 50, 50 });

    auto stripeWhite = sf::RectangleShape{ { 14.f, HEIGHT } };
    stripeWhite.setFillColor(sf::Color::White);

    auto stripeRed = sf::RectangleShape{ { 14.f, HEIGHT } };
    stripeRed.setFillColor(sf::Color::Red);

    auto animation = sf::Clock{};
    auto moved = 0.f;

    while (window.isOpen())
    {
        if (animation.getElapsedTime().asMilliseconds() > 10)
        {
            animation.restart();
            moved += 5.f;
            if (moved > HEIGHT*2)
            {
	            moved = 0.f;
            }
        }

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
	            window.close();
            }
        }

        window.clear();

        grass.setPosition(0.f, 0.f);
        window.draw(grass);

        grass.setPosition(762.f, 0.f);
        window.draw(grass);

        window.draw(road);

        for (auto i = 0U; i < STRIPES_COUNT; ++i)
        {
            stripeWhite.setPosition({ 262.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - (HEIGHT * 2) });
            window.draw(stripeWhite);
        }

        for (auto i = 0U; i < STRIPES_COUNT; ++i)
        {
            stripeRed.setPosition({ 262.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - HEIGHT });
            window.draw(stripeRed);
        }

        for (auto i = 0U; i < STRIPES_COUNT; ++i)
        {
            stripeWhite.setPosition({ 504.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - HEIGHT });
            window.draw(stripeWhite);
        }

        for (auto i = 0U; i < STRIPES_COUNT; ++i)
        {
            stripeWhite.setPosition({ 748.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - (HEIGHT * 2) });
            window.draw(stripeWhite);
        }

        for (auto i = 0U; i < STRIPES_COUNT; ++i)
        {
            stripeRed.setPosition({ 748.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - HEIGHT });
            window.draw(stripeRed);
        }

        for (auto i = 0U; i < STRIPES_COUNT; ++i)
        {
            greyLight.setPosition({ 0.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - (HEIGHT * 2) });
            window.draw(greyLight);
        }

        for (auto i = 0; i < STRIPES_COUNT; ++i)
        {
            greyDark.setPosition({ 0.f, (moved + (static_cast<float>(i) * HEIGHT * 2)) - HEIGHT });
            window.draw(greyDark);
        }

        window.display();
    }
}
