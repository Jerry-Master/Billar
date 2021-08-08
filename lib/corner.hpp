#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

class CornerShape : public sf::Shape
{
public :

    explicit CornerShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f),
                         const double angle0=0, const double angle1=0);

    void setRadius(const sf::Vector2f& radius);

    const sf::Vector2f& getRadius() const;

    virtual std::size_t getPointCount() const;

    virtual sf::Vector2f getPoint(std::size_t index) const;

    bool isInside(sf::Vector2f pos, double rad);

private :

    sf::Vector2f m_radius;
    double m_angle0, m_angle1;
};