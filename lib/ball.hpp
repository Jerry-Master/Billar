#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"

class Ball {
    private:
        double radius, delta = 0.1, friction = -0.05;
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::Vector2f acc;

    public:
        Ball();
        Ball(double radius, double pos_x, double pos_y);
        Ball(double radius, sf::Vector2f pos);

        void draw(sf::RenderWindow& window);

        void update();

        void setVel(sf::Vector2f vel);
        sf::Vector2f getPos();

        bool collides(Ball other);
        void reflect(sf::Vector2f n, sf::Vector2f prev_pos);
        int outOfTable(double up, double down, double left, double right);
};