#include "stick.hpp"
#include <iostream>
using namespace std;

Stick::Stick(const sf::Texture& texture1, const sf::Texture& texture2, 
             const sf::Texture& texture3, const sf::Texture& texture4,
             double length_, double width_, double window_width_,
             double window_height_){

    length = length_;
    width = width_;
    window_width = window_width_;
    window_height = window_height_;

    view = sf::View(sf::FloatRect(0,0, window_width, window_height)); // container
    tip = trapezium(texture1, 0.3*width, 0.3*width, 0.02*length);
    shaft = trapezium(texture2, 0.5*width, 0.3*width, 0.48*length);
    butt = trapezium(texture3, width, 0.5*width, 0.48*length);
    bumper = trapezium(texture4, 0.7*width, width, 0.02*length);
    sf::Vector2f offset(window_width / 2, window_height/2);
    v1 = sf::Vector2f(0.2*width, -0.02*length);
    v2 = sf::Vector2f(0.1*width, -0.5*length);
    v3 = sf::Vector2f(-0.15*width, -0.98*length);
    v4 = sf::Vector2f(0, -length);
    tip.setPosition(offset + rotateV(v1,90));
    tip.setRotation(90);
    shaft.setPosition(offset + rotateV(v2,90));
    shaft.setRotation(90);
    butt.setPosition(offset + rotateV(v3,90));
    butt.setRotation(90);
    bumper.setPosition(offset + rotateV(v4,90));
    bumper.setRotation(90);
}

void Stick::draw(sf::RenderWindow& window){
    view.setRotation(angle);
    window.setView(view);
    window.draw(tip);
    window.draw(shaft);
    window.draw(butt);
    window.draw(bumper);
    window.setView(window.getDefaultView());
}

void Stick::move(double x, double y){
    view.setCenter(rotateV(sf::Vector2f(-x+window_width / 2,-y+window_height/2),angle)+sf::Vector2f(window_width / 2,window_height/2));
    sf::Vector2f offset(window_width / 2, window_height/2);
    tip.setPosition(offset + rotateV(v1,90));
    tip.setRotation(90);
    shaft.setPosition(offset + rotateV(v2,90));
    shaft.setRotation(90);
    butt.setPosition(offset + rotateV(v3,90));
    butt.setRotation(90);
    bumper.setPosition(offset + rotateV(v4,90));
    bumper.setRotation(90);
}
void Stick::move(sf::Vector2f pos){
    this->move(pos.x, pos.y);
}

void Stick::rotate(double x, double y, sf::Vector2f ball){
    sf::Vector2f v = sf::Vector2f(x,y) - ball;
    angle = -atan(v.y / v.x) * 360 / (2 * M_PI);
    if ((v.x < 0 and v.y > 0) or (v.x < 0 and v.y < 0)){
        angle += 180;
    }
    view.setCenter(rotateV(sf::Vector2f(-x+window_width / 2,-y+window_height/2),angle)+sf::Vector2f(window_width / 2,window_height/2));
}
void Stick::rotate(sf::Vector2f pos, sf::Vector2f ball){
    this->rotate(pos.x, pos.y, ball);
}

void Stick::charge(double x, double y, double time){
    view.setCenter(rotateV(sf::Vector2f(-x+window_width / 2,-y+window_height/2),angle)+sf::Vector2f(window_width / 2,window_height/2));
    sf::Vector2f offset(window_width / 2+time, window_height/2);
    tip.setPosition(offset + rotateV(v1,90));
    tip.setRotation(90);
    shaft.setPosition(offset + rotateV(v2,90));
    shaft.setRotation(90);
    butt.setPosition(offset + rotateV(v3,90));
    butt.setRotation(90);
    bumper.setPosition(offset + rotateV(v4,90));
    bumper.setRotation(90);
}