#include <SFML/Graphics.hpp>
#include "table.hpp"
#include "stick.hpp"
#include "ball.hpp"
using namespace std; 

const int WIDTH = 2000;
const int HEIGHT = 1300;
const vector<int> order = {6,15,13,3,12,9,7,14,4,2,8,10,11,5,1};
    
using Balls = list<Ball>;

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

    double rad = 25;
    Stick stick(texture1, texture2, texture3, texture4, 1000, 30, WIDTH, HEIGHT, rad);

    Balls balls(16);
    vector<sf::Texture> textures(16);
    int cont = 0;
    list<Ball>::iterator it = balls.begin();
    for (int j = 0; j <= 4; j++){
        for (int i = 0; i <= 4-j; i++){
            Ball new_ball = Ball(rad, 500 + rad*2*j * 0.866, 
                                 650 - 6*rad + rad*2*i + rad*2*j * 0.5);
            textures[cont].loadFromFile("images/balls/"+ to_string(order[cont]) + ".jpg");
            new_ball.addTexture(&textures[cont]);
            *it = new_ball;
            cont++; it++;
        }
    }
    Ball new_ball = Ball(rad, 1300, 650-rad);
    new_ball.addTexture(&texture2);
    *it = new_ball;

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                charge = true;
            }
            if (event.type == sf::Event::MouseButtonReleased or 
                event.type == sf::Event::KeyReleased){
                if (charge) init_charge = true;
                move = rotate = charge = false;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (move){
            stick.move(balls.back().getPos().x, balls.back().getPos().y);
        }
        if (rotate){
            stick.rotate(mousePos.x, mousePos.y, balls.back().getPos());
        }
        if (charge){
            stick.charge(balls.back().getPos().x, balls.back().getPos().y, time++);
            size_ = time;
        } else if (init_charge){
            stick.charge(balls.back().getPos().x, balls.back().getPos().y, time);
            time -= 10;
            if (time < 0) {
                init_charge = false;
                balls.back().setVel(resize(balls.back().getPos() - sf::Vector2f(mousePos.x,mousePos.y), size_ * 0.3));
            }
        }
        pool_table.draw(window);
        vector<sf::Vector2f> prev_pos(balls.size());
        int i = 0;
        for (it = balls.begin(); it != balls.end(); ++it){
            prev_pos[i] = it->getPos();
            it->update();
            it->draw(window);
            i++;
        }
        stick.draw(window);

        // end the current frame
        window.display();

        // Compute collisions
        i = 0;
        for (it = balls.begin(); it != balls.end(); ++it){
            int j = i;
            for (auto it2 = it; it2 != balls.end(); ++it2){
                if (it != it2 and it->collides(*it2)){
                    it->reflectCollision(*it2, prev_pos[i], prev_pos[j]);
                }
                j++;
            }
            i++;
        }
        i = 0;
        for (it = balls.begin(); it != balls.end(); it++){
            int out = it->outOfTable(HEIGHT/2 - cloth_height/2+50,HEIGHT/2 + cloth_height/2-50,
                                          WIDTH/2 - cloth_width/2+50,WIDTH/2 + cloth_width/2-50);
            if (out != -1) {
                sf::Vector2f n;
                if (out == 0 or out == 1){
                    n = sf::Vector2f(0,1);
                } else if(out == 2 or out == 3){
                    n = sf::Vector2f(1,0);
                }
                it->reflect_update(n, prev_pos[i]);
            }
            i++; 
        }    

        // Check for balls entering the holes
        for (it = balls.begin(); it != balls.end(); ++it){
            if (pool_table.entered_hole(it->getPos(), it->getRadius())){
                if (++it == balls.end()){
                    balls.back().setPos(1300, 650-rad);
                    balls.back().setVel(0,0);
                } else {
                    balls.erase(--it);
                }
            }
        }      
    }
}