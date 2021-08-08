#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"

class Ball {
    private:
        double radius, delta = 0.1, friction = -0.05;
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::Vector2f acc;
        sf::Texture* texture;
        bool has_texture = false;

    public:
        Ball();
        Ball(double radius, double pos_x, double pos_y);
        Ball(double radius, sf::Vector2f pos);
        void addTexture(sf::Texture* texture_);

        void draw(sf::RenderWindow& window);
        // Update position based on acceleration, velocity and physics
        void update();

        sf::Vector2f getVel();
        void setVel(sf::Vector2f vel);
        void setVel(double x, double y);
        // Get position of the center of the ball
        sf::Vector2f getPos();
        void setPos(sf::Vector2f pos_);
        void setPos(double x, double y);
        double getRadius();

        // Checks if this collides with other
        bool collides(Ball other);
        // Reflects the vel vector (or v vector) respect to the n vector
        sf::Vector2f reflect(sf::Vector2f n, sf::Vector2f v);
        void reflect_update(sf::Vector2f n, sf::Vector2f prev_pos);
        // Updates velocities of two balls after collision
        void reflectCollision(Ball& other, sf::Vector2f prev_pos, sf::Vector2f prev_pos_other);
        // Checks if the ball is out of the table
        int outOfTable(double up, double down, double left, double right);
};