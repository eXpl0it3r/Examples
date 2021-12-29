#include "Lightning.hpp"

Lightning::Lightning(const unsigned long numberOfSegments, const unsigned int thickness, const sf::Color color, const sf::Color fadeColor) :
    m_rand{ 42 },
	m_color{ color },
    m_fadeColor{ fadeColor },
    m_numberOfSegments{ numberOfSegments },
    m_thickness{ thickness }
{
    m_segments.reserve(m_numberOfSegments);
}

void Lightning::generate()
{
	m_segments.clear();

	m_segments.push_back(0.f); // The start point of the lightning is centered

	for (auto c = std::size_t{ 1u }; c < m_numberOfSegments - 1u; ++c)
	{
		m_segments.push_back(rand(-1.f, 1.f));
	}

	m_segments.push_back(0.f); // The end point of the lightning is also centered
}

const sf::Color& Lightning::getColor() const
{
    return m_color;
}

void Lightning::setColor(const sf::Color& color)
{
    m_color = color;
}

const sf::Color& Lightning::getFadeColor() const
{
    return m_color;
}

void Lightning::setFadeColor(const sf::Color& color)
{
    m_color = color;
}

const sf::Vector2f& Lightning::getSize() const
{
    return m_size;
}

void Lightning::setSize(const sf::Vector2f& size)
{
    m_size = size;
}

float Lightning::rand(const float low, const float high)
{
    return static_cast<float>(m_rand()) / static_cast<float>(std::minstd_rand::max()) * (high - low) + low;
}

sf::VertexArray Lightning::line(const sf::Vector2f start, const sf::Vector2f end, const unsigned int thickness, const sf::Color color)
{
    auto line = sf::VertexArray{ sf::Lines, std::size_t{ 2u } * thickness };
    for (auto i = std::size_t{ 0u }; i < std::size_t{ 2u } * thickness; i += 2u)
    {
        line[i].position = start;
        line[i].position.x += static_cast<float>(i) / 2.f;
        line[i].color = color;
        line[i + 1u].position = end;
        line[i + 1u].position.x += static_cast<float>(i) / 2.f;
        line[i + 1u].color = color;
    }

    return line;
}

void Lightning::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto color = sf::Color{};
	auto colorStep = sf::Color{};

    // If the thickness is 1.0 then draw using only the main color. Otherwise calculate the amount to fade the fade color each iteration
    if (m_thickness == 1u)
    {
	    color = m_color;
    }
    else
    {
        color = m_fadeColor;

        // sf::Color doesn't provide the minus or division operators, so we'll have to make the calculations component by component
        const auto colorDifference = sf::Color{ static_cast<sf::Uint8>(m_color.r - m_fadeColor.r),
        	                                    static_cast<sf::Uint8>(m_color.g - m_fadeColor.g),
                                                static_cast<sf::Uint8>(m_color.b - m_fadeColor.b),
                                                static_cast<sf::Uint8>(m_color.a - m_fadeColor.a) };
        colorStep = sf::Color{ static_cast<sf::Uint8>(colorDifference.r / static_cast<sf::Uint8>(m_thickness - 1)),
                               static_cast<sf::Uint8>(colorDifference.g / static_cast<sf::Uint8>(m_thickness - 1)),
                               static_cast<sf::Uint8>(colorDifference.b / static_cast<sf::Uint8>(m_thickness - 1)),
                               static_cast<sf::Uint8>(colorDifference.a / static_cast<sf::Uint8>(m_thickness - 1)) }; // Increase the fade color by this each iteration.
    }

    const auto segmentHeight = m_size.y / static_cast<float>(m_numberOfSegments - 1);
    const auto halfWidth = m_size.x / 2.f;
    const auto halfThickness = static_cast<float>(m_thickness) / 2.f;

    states.transform *= getTransform();

    // Draw multiple lightnings, decreasing the thickness by 1.0 until we reach thickness 1.0 (or less)
    for (auto t = m_thickness; t >= 1u; --t, color += colorStep)
    {
        for (auto c = std::size_t{ 0u }; c < m_numberOfSegments - 1; ++c)
	    {
	    	const auto start = sf::Vector2f{ m_segments[c] * (halfWidth - halfThickness) + halfWidth, segmentHeight * static_cast<float>(c) };
	    	const auto end = sf::Vector2f{ m_segments[c + 1u] * (halfWidth - halfThickness) + halfWidth, segmentHeight * static_cast<float>(c + 1u) };

	    	target.draw(line(start, end, t, color), states);
	    }
    }
}
