#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const double EPS = 1e-6;

inline sf::ConvexShape trapezium(const sf::Texture& texture_border, 
                         double border_width,
                         double cloth_width){
    sf::ConvexShape convex;

    // resize it to 5 points
    convex.setPointCount(4);

    // define the points
    convex.setPoint(0, sf::Vector2f(0.f, 0.f));
    convex.setPoint(1, sf::Vector2f(cloth_width + border_width, 0.f));
    convex.setPoint(3, sf::Vector2f(border_width, border_width));
    convex.setPoint(2, sf::Vector2f(cloth_width, border_width));
    convex.setTexture(&texture_border);

    return convex;
}

inline sf::ConvexShape trapezium(const sf::Texture& texture_border, 
                         double base0, double base1,
                         double height){
    sf::ConvexShape convex;

    // resize it to 5 points
    convex.setPointCount(4);

    // define the points
    convex.setPoint(0, sf::Vector2f(0.f, 0.f));
    convex.setPoint(1, sf::Vector2f(base0, 0.f));
    convex.setPoint(3, sf::Vector2f((base0-base1)/2, height));
    convex.setPoint(2, sf::Vector2f((base0-base1)/2+base1, height));
    convex.setTexture(&texture_border);

    return convex;
}

inline sf::Vector2f rotateV(sf::Vector2f v, double angle){
    angle = angle * M_PI / 180;
    return sf::Vector2f(cos(angle) * v.x - sin(angle) * v.y,
                       sin(angle) * v.x + cos(angle) * v.y);
}

inline sf::Vector2f resize(sf::Vector2f v, double size){
    double abs = sqrt(v.x*v.x + v.y*v.y);
    return sf::Vector2f(v.x * size / abs, v.y * size / abs);
}
inline double size(sf::Vector2f v){
    return sqrt(v.x*v.x + v.y*v.y);
}
inline double scalar(sf::Vector2f v, sf::Vector2f w){
    return v.x*w.x + v.y*w.y;
}
inline bool sameDir(sf::Vector2f v, sf::Vector2f w){
    v = resize(v, 1);
    w = resize(w, 1);

    double angle = acos(scalar(v,w));

    return angle < EPS;
}
// Decompose v in directions w and perpendicular to w
inline vector<sf::Vector2f> decompose(sf::Vector2f v, sf::Vector2f w){
    w = resize(w, 1);
    sf::Vector2f v1 = resize(w, scalar(v,w));
    sf::Vector2f v2 = v - v1;
    return {v1, v2};
}
