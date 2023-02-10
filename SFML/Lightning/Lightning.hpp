#pragma once

#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

class Lightning final : public sf::Transformable, public sf::Drawable
{
public:
	explicit Lightning(const unsigned long numberOfSegments, const unsigned int thickness = 1, const sf::Color color = sf::Color::Blue, const sf::Color fadeColor = sf::Color::Black);

    void generate();
    const sf::Color& getColor() const;
    void setColor(const sf::Color& color);
    const sf::Color& getFadeColor() const;
    void setFadeColor(const sf::Color& color);
    const sf::Vector2f& getSize() const;
    void setSize(const sf::Vector2f& size);

private:
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    float rand(float low, float high);
	static sf::VertexArray line(sf::Vector2f start, sf::Vector2f end, unsigned int thickness, sf::Color color);

private:
    std::minstd_rand   m_rand;

    sf::Color          m_color;
    sf::Color          m_fadeColor;
    sf::Vector2f       m_size;      // Size of the lightning

    std::size_t        m_numberOfSegments;
    unsigned int       m_thickness;

    std::vector<float> m_segments;  // Contains the x-position of each segment (-1.0 - +1.0), multiply with width to get final position
};
