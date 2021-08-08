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
void Ball::addTexture(sf::Texture* texture_){
    texture = texture_;
    has_texture = true;
}

void Ball::draw(sf::RenderWindow& window){
    sf::CircleShape circle(radius);
    circle.setPosition(pos);
    if (has_texture) circle.setTexture(texture);
    window.draw(circle);
}

void Ball::update(){
    if (abs(vel.x) > 0 or abs(vel.y) > 0){
        pos = pos + sf::Vector2f(delta * vel.x, delta * vel.y);
        vel = vel + sf::Vector2f(delta * vel.x * friction, 
                                 delta * vel.y * friction);
    }
}

sf::Vector2f Ball::getVel(){
    return vel;
}
void Ball::setVel(sf::Vector2f vel_){
    vel = vel_;
}
void Ball::setVel(double x, double y){
    vel = sf::Vector2f(x,y);
}

sf::Vector2f Ball::getPos(){
    return pos + sf::Vector2f(radius, radius);
}
void Ball::setPos(sf::Vector2f pos_){
    pos = pos_;
}
void Ball::setPos(double x, double y){
    pos = sf::Vector2f(x, y);
}

double Ball::getRadius(){
    return radius;
}

bool Ball::collides(Ball other){
    return (size(this->getPos() - other.getPos()) < 2*radius-0.1);
}

sf::Vector2f Ball::reflect(sf::Vector2f n, sf::Vector2f v){
    return float(2 * scalar(n, v) / (size(n)*size(n))) * n - v;
}

void Ball::reflect_update(sf::Vector2f n, sf::Vector2f prev_pos){
    pos = prev_pos - sf::Vector2f(radius, radius);
    vel = reflect(n, vel);
}

void Ball::reflectCollision(Ball& other, sf::Vector2f prev_pos, sf::Vector2f prev_pos_other){
    pos = prev_pos - sf::Vector2f(radius, radius);
    other.setPos(prev_pos_other - sf::Vector2f(other.getRadius(), other.getRadius()));

    sf::Vector2f dir = prev_pos - other.getPos();
    sf::Vector2f v1 = vel;
    sf::Vector2f v2 = other.getVel();

    vector<sf::Vector2f> dec1 = decompose(v1, dir);
    vector<sf::Vector2f> dec2 = decompose(v2, dir);

    setVel(dec1[1]+dec2[0]);
    other.setVel(dec2[1]+dec1[0]);
}

int Ball::outOfTable(double up, double down, double left, double right){
    if (pos.x < left) return 0;
    if (pos.x + 2*radius > right) return 1;
    if (pos.y < up) return 2;
    if (pos.y + 2*radius > down) return 3;
    return -1;
}