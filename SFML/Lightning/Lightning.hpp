#ifndef LIGHTNING_HPP
#define LIGHTNING_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Lightning : public sf::Transformable, public sf::Drawable
{
public:
    Lightning(const unsigned long& noSegments, const unsigned int& thickness = 1, const sf::Color& color = sf::Color::Blue, const sf::Color& fadeColor = sf::Color::Black);
    void generate();
    const sf::Color& getColor() const;
    void setColor(const sf::Color& color);
    const sf::Color& getFadeColor() const;
    void setFadeColor(const sf::Color& color);
    const sf::Vector2f& getSize();
    void setSize(const float& width, const float& height);
    void setSize(const sf::Vector2f& size);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray line(sf::Vector2f start, sf::Vector2f end, unsigned int thickness, sf::Color color) const;
    float rand(float low, float high) const;

private:
    sf::Color          m_color;
    sf::Color          m_fadeColor;
    sf::Vector2f       m_size;      // Size of the lightning

    unsigned long      m_noSegments;
    unsigned int       m_thickness;

    std::vector<float> m_segments;  // Contains the x-position of each segment (-1.0 - +1.0), multiply with width to get final position
};

#endif // LIGHTNING_HPP
