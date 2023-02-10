// Warning: This code isn't nice at all, so don't even think about using it in production code. ;-)

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
    auto window = sf::RenderWindow{ sf::VideoMode{ { 1024u, 768u } }, "Road" };
    window.setFramerateLimit(60u);

    auto grass = sf::RectangleShape{ { 262.f, 768.f } };
    grass.setFillColor({ 0u, 100u, 0u });

    auto road = sf::RectangleShape{ { 500.f, 768.f } };
    road.setFillColor({ 50u, 50u, 50u });
    road.setPosition({ 262.f, 0.f });

    constexpr auto Height = 70.f;
    constexpr auto StripesCount = 7u;

    auto greyLight = sf::RectangleShape{ { 1024.f, Height } };
    greyLight.setFillColor({ 50u, 50u, 50u, 20u });

    auto greyDark = sf::RectangleShape{ { 1024.f, Height } };
    greyDark.setFillColor({ 50u, 50u, 50u, 50u });

    auto stripeWhite = sf::RectangleShape{ { 14.f, Height } };
    stripeWhite.setFillColor(sf::Color::White);

    auto stripeRed = sf::RectangleShape{ { 14.f, Height } };
    stripeRed.setFillColor(sf::Color::Red);

    auto animation = sf::Clock{};
    auto moved = 0.f;

    while (window.isOpen())
    {
        if (animation.getElapsedTime().asMilliseconds() > 10)
        {
            animation.restart();
            moved += 5.f;

            if (moved > Height * 2.f)
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

        grass.setPosition({ 0.f, 0.f });
        window.draw(grass);

        grass.setPosition({ 762.f, 0.f });
        window.draw(grass);

        window.draw(road);

        for (auto i = 0u; i < StripesCount; ++i)
        {
            stripeWhite.setPosition({ 262.f, (moved + (static_cast<float>(i) * Height * 2.f)) - (Height * 2.f) });
            window.draw(stripeWhite);
        }

        for (auto i = 0u; i < StripesCount; ++i)
        {
            stripeRed.setPosition({ 262.f, (moved + (static_cast<float>(i) * Height * 2.f)) - Height });
            window.draw(stripeRed);
        }

        for (auto i = 0u; i < StripesCount; ++i)
        {
            stripeWhite.setPosition({ 504.f, (moved + (static_cast<float>(i) * Height * 2.f)) - Height });
            window.draw(stripeWhite);
        }

        for (auto i = 0u; i < StripesCount; ++i)
        {
            stripeWhite.setPosition({ 748.f, (moved + (static_cast<float>(i) * Height * 2.f)) - (Height * 2.f) });
            window.draw(stripeWhite);
        }

        for (auto i = 0u; i < StripesCount; ++i)
        {
            stripeRed.setPosition({ 748.f, (moved + (static_cast<float>(i) * Height * 2.f)) - Height });
            window.draw(stripeRed);
        }

        for (auto i = 0u; i < StripesCount; ++i)
        {
            greyLight.setPosition({ 0.f, (moved + (static_cast<float>(i) * Height * 2.f)) - (Height * 2.f) });
            window.draw(greyLight);
        }

        for (auto i = 0u; i < StripesCount; ++i)
        {
            greyDark.setPosition({ 0.f, (moved + (static_cast<float>(i) * Height * 2.f)) - Height });
            window.draw(greyDark);
        }

        window.display();
    }
}
