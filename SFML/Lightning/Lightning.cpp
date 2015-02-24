#include "Lightning.hpp"

#include <ctime>
#include <cstdio> // rand

Lightning::Lightning(const unsigned long& noSegments, const unsigned int& thickness, const sf::Color& color, const sf::Color& fadeColor) :
    m_color(color),
    m_fadeColor(fadeColor),
    m_noSegments(noSegments),
    m_thickness(thickness)
{
    m_segments.reserve(m_noSegments);
}

void Lightning::generate()
{
  sf::Vector2f start;
  sf::Vector2f end(0.f, 0.f);

  m_segments.clear();

  m_segments.push_back(0.f); // The start point of the lightning is centered

  for(unsigned long c = 1; c < m_noSegments - 1; ++c)
    m_segments.push_back(rand(-1.f, 1.f));

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

const sf::Vector2f& Lightning::getSize()
{
    return m_size;
}

void Lightning::setSize(const float& width, const float& height)
{
    m_size.x = width;
    m_size.y = height;
}

void Lightning::setSize(const sf::Vector2f& size)
{
    m_size = size;
}

float Lightning::rand(float low, float high) const
{
    return static_cast<float>(std::rand()) / RAND_MAX * (high - low) + low;
}

sf::VertexArray Lightning::line(sf::Vector2f start, sf::Vector2f end, unsigned int thickness, sf::Color color) const
{
    sf::VertexArray line(sf::Lines, 2*thickness);
    for(unsigned int i = 0; i < 2*thickness; i += 2)
    {
        line[i].position = start;
        line[i].position.x += i/2.f;
        line[i].color = color;
        line[i+1].position = end;
        line[i+1].position.x += i/2.f;
        line[i+1].color = color;
    }

    return line;
}

void Lightning::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Vector2f start, end;
    sf::Color color, colorDifference, colorStep;

    // If the thickness is 1.0 then draw using only the main color. Otherwise calculate the amount to fade the fade color each iteration
    if(m_thickness == 1)
        color = m_color;
    else
    {
        color = m_fadeColor;

        // sf::Color doesn't provide the minus or division operators, so we'll have to make the calculations component by component
        colorDifference = sf::Color(m_color.r - m_fadeColor.r,
                                    m_color.g - m_fadeColor.g,
                                    m_color.b - m_fadeColor.b,
                                    m_color.a - m_fadeColor.a);
        colorStep = sf::Color(colorDifference.r / static_cast<sf::Uint8>(m_thickness - 1),
                            colorDifference.g / static_cast<sf::Uint8>(m_thickness - 1),
                            colorDifference.b / static_cast<sf::Uint8>(m_thickness - 1),
                            colorDifference.a / static_cast<sf::Uint8>(m_thickness - 1)); // Increase the fade color by this each iteration.
    }

    float segmentHeight = m_size.y / (m_noSegments - 1.0f);
    float halfWidth = m_size.x / 2;
    float halfThickness = static_cast<float>(m_thickness) / 2;

    states.transform *= getTransform();

    // Draw multiple lightnings, decreasing the thickness by 1.0 until we reach thickness 1.0 (or less)
    for(float t = static_cast<float>(m_thickness); t >= 1.0f; --t, color += colorStep)
        for(unsigned long c = 0; c < m_noSegments - 1; ++c)
        {
            start.x = m_segments[c] * (halfWidth - halfThickness) + halfWidth;
            start.y = segmentHeight * c;
            end.x = m_segments[c + 1] * (halfWidth - halfThickness) + halfWidth;
            end.y = segmentHeight * (c + 1);

            target.draw(line(start, end, t, color), states);
        }
}
