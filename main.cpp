#include <iostream>
#include <SFML/Graphics.hpp>
#include "table.hpp"
#include "stick.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include <vector>
using namespace std; 

const int WIDTH = 2000;
const int HEIGHT = 1300;
    
using Balls = vector<Ball>;

int main(){
    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window", sf::Style::Default, settings);
    sf::Texture texture_cloth, texture_border, texture_corner,
    texture1, texture2, texture3, texture4;
    texture_cloth.loadFromFile("images/cloth.jpg");
    texture_border.loadFromFile("images/wood.jpg");
    texture_corner.loadFromFile("images/black.jpg");
    texture1.loadFromFile("images/blue.jpg");
    texture2.loadFromFile("images/light-wood.jpg");
    texture3.loadFromFile("images/dark-wood.jpg");
    texture4.loadFromFile("images/black-wood.jpg");

    int cloth_width = 1500;
    int cloth_height = cloth_width / 2;
    Table pool_table(texture_cloth, texture_border, texture_corner, 100, 
                     cloth_width, cloth_height, WIDTH, HEIGHT);
    bool move=false, rotate=false, charge=false, init_charge=false;

    Stick stick(texture1, texture2, texture3, texture4, 1000, 30, WIDTH, HEIGHT);

    Balls balls(22);
    int cont = 0;
    double rad = 20;
    for (int j = 0; j <= 5; j++){
        for (int i = 0; i <= 5-j; i++){
            balls[cont++] = Ball(rad, 500 + rad*2*j * 0.866, 
                                 650 - 6*rad + rad*2*i + rad*2*j * 0.5);
        }
    }
    balls[cont] = Ball(rad, 1300, 650-rad);
    int time = 0;
    double size_ = 0;
    // run the program as long as the window is open
    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                move = true;
                rotate = true;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){ 
                charge = true;
            }
            if (event.type == sf::Event::MouseButtonReleased){
                if (charge) init_charge = true;
                move = rotate = charge = false;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (move){
            stick.move(mousePos.x, mousePos.y);
        }
        if (rotate){
            stick.rotate(mousePos.x, mousePos.y, balls[21].getPos());
        }
        if (charge){
            stick.charge(mousePos.x, mousePos.y, time++);
            size_ = time;
        } else if (init_charge){
            stick.charge(mousePos.x, mousePos.y, time);
            time -= 10;
            if (time < 0) {
                init_charge = false;
                balls[21].setVel(resize(balls[21].getPos() - sf::Vector2f(mousePos.x,mousePos.y), size_/5));
            }
        }
        pool_table.draw(window);
        stick.draw(window);
        vector<sf::Vector2f> prev_pos(22);
        for (int i = 0; i < 22; i++){
            prev_pos[i] = balls[i].getPos();
            balls[i].update();
            balls[i].draw(window);
        }
        for (int i = 0; i < 22; i++){
            for (int j = 0; j < 22; j++){
                if (i != j and balls[i].collides(balls[j])){
                    sf::Vector2f p = prev_pos[i] - balls[j].getPos();
                    sf::Vector2f n = sf::Vector2f(-p.y, p.x);
                    balls[i].reflect(n, prev_pos[i]);
                }
            }
        }
        for (int i = 0; i < 22; i++){
            int out = balls[i].outOfTable(HEIGHT/2 - cloth_height/2+50,HEIGHT/2 + cloth_height/2-50,
                                          WIDTH/2 - cloth_width/2+50,WIDTH/2 + cloth_width/2-50);
            if (out != -1) {
                if (i == 21) cout << "reflect" << endl;
                sf::Vector2f n;
                if (out == 0 or out == 1){
                    n = sf::Vector2f(0,1);
                } else if(out == 2 or out == 3){
                    n = sf::Vector2f(1,0);
                }
                balls[i].reflect(n, prev_pos[i]);
            }
        }

        // end the current frame
        window.display();
    }
}