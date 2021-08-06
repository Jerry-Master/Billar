#include "ball.hpp"

Ball::Ball(){
    radius = 20;
    pos.x = 0;
    pos.y = 0;
}
Ball::Ball(double radius_, double pos_x, double pos_y){
    radius = radius_;
    pos.x = pos_x;
    pos.y = pos_y;
}
Ball::Ball(double radius_, sf::Vector2f pos_){
    radius = radius_;
    pos = pos_;
}

void Ball::draw(sf::RenderWindow& window){
    sf::CircleShape circle(radius);
    circle.setPosition(pos);
    window.draw(circle);
}

void Ball::update(){
    if (abs(vel.x) > 0 or abs(vel.y) > 0){
        pos = pos + sf::Vector2f(delta * vel.x, delta * vel.y);
        vel = vel + sf::Vector2f(delta * vel.x * friction, 
                                 delta * vel.y * friction);
    }
}

void Ball::setVel(sf::Vector2f vel_){
    vel = vel_;
}

sf::Vector2f Ball::getPos(){
    return pos + sf::Vector2f(radius, radius);
}

bool Ball::collides(Ball other){
    return (size(this->getPos() - other.getPos()) < 2*radius-0.1);
}
void Ball::reflect(sf::Vector2f n, sf::Vector2f prev_pos){
    pos = prev_pos - sf::Vector2f(radius, radius);
    vel = float(2 * scalar(n, vel) / (size(n)*size(n))) * n - vel;
}
int Ball::outOfTable(double up, double down, double left, double right){
    if (pos.x < left) return 0;
    if (pos.x + 2*radius > right) return 1;
    if (pos.y < up) return 2;
    if (pos.y + 2*radius > down) return 3;
    return -1;
}