#include "corner.hpp"

CornerShape::CornerShape(const sf::Vector2f& radius,
                        const double angle0, const double angle1) :
m_radius(radius), m_angle0(angle0 * 2 * M_PI / 360), m_angle1(angle1 * 2 * M_PI / 360)
{
    update();
}

void CornerShape::setRadius(const sf::Vector2f& radius)
{
    m_radius = radius;
    update();
}

const sf::Vector2f& CornerShape::getRadius() const
{
    return m_radius;
}

std::size_t CornerShape::getPointCount() const
{
    return 1000; // fixed, but could be an attribute of the class if needed
}

sf::Vector2f CornerShape::getPoint(std::size_t index) const
{
    static const float pi = 3.141592654f;

    float angle = index * 2 * pi / getPointCount();
    sf:: Vector2f center2(0,0);
    double radius;

    double beta2 = std::asin(m_radius.y / m_radius.x * std::sin((m_angle1-m_angle0)/2));
    if ((angle >= 2*pi - beta2 and angle <= 2*pi) or 
        (angle >= 0 and angle <= beta2)){

        radius = m_radius.x;
        double aux = 2 * m_radius.y * std::cos(pi-(m_angle1-m_angle0)/2);
        double rad_center = (aux + std::sqrt(aux*aux - 4*(m_radius.y*m_radius.y - m_radius.x*m_radius.x)))/2;
        center2 = sf::Vector2f(rad_center, 0);
            
    } else if ((angle > beta2 and angle < (m_angle1-m_angle0)/2) or
                (angle < 2*pi - beta2 and angle > 2*pi - (m_angle1-m_angle0)/2)){
        radius = m_radius.y;
        angle = (m_angle1-m_angle0)/2;
    } else {
        radius = m_radius.y;
    }
    float x = std::cos(-angle) * radius;
    float y = std::sin(-angle) * radius;

    return sf::Vector2f(x, y) - center2;
}

bool CornerShape::isInside(sf::Vector2f pos, double rad){
    return size(getPosition() - pos) < m_radius.x - m_radius.y - rad;
}