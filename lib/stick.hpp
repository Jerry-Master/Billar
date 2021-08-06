#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include <cmath>

class Stick{

    private:
        double length, width, angle, window_width, window_height;
        sf::ConvexShape tip, shaft, butt, bumper;
        sf::View view;
        sf::Vector2f v1, v2, v3, v4;

    public:
        Stick(const sf::Texture& texture1, const sf::Texture& texture2, 
              const sf::Texture& texture3, const sf::Texture& texture4,
              double lenght, double width, double window_width_,
              double window_height_);

        void draw(sf::RenderWindow& window);

        void move(double x, double y);
        void move(sf::Vector2f pos);

        void rotate(double x, double y, sf::Vector2f ball);
        void rotate(sf::Vector2f pos, sf::Vector2f ball);

        void charge(double x, double y, double time);

};