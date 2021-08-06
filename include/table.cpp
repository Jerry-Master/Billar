#include "table.hpp"

Table::Table(const sf::Texture& texture_cloth, const sf::Texture& texture_border,
          const sf::Texture& texture_corner,
          double border_width, double cloth_width, double cloth_height,
          double WIDTH, double HEIGHT){
    cloth = sf::RectangleShape(sf::Vector2f(cloth_width, cloth_height));
    cloth.setPosition(WIDTH/2 - cloth_width/2, 
                    HEIGHT/2- cloth_height/2);
    cloth.setTexture(&texture_cloth);
    
    up = trapezium(texture_border, border_width, cloth_width);
    up.setPosition(cloth.getPosition()-sf::Vector2f(border_width/2,border_width/2));

    down = trapezium(texture_border, border_width, cloth_width);
    down.setOrigin(down.getOrigin() + sf::Vector2f((border_width+cloth_width)/2,border_width/2));
    down.rotate(180);
    down.setOrigin(down.getOrigin() + sf::Vector2f((border_width+cloth_width)/2,border_width/2));
    down.setPosition(cloth.getPosition()-sf::Vector2f(border_width/2,border_width/2-cloth_height));

    left = trapezium(texture_border, border_width, cloth_height);
    left.setOrigin(left.getOrigin() + sf::Vector2f((border_width+cloth_height)/2,border_width/2));
    left.rotate(-90);
    left.setOrigin(left.getOrigin() - sf::Vector2f(-(border_width+cloth_height)/2,border_width/2));
    left.setPosition(cloth.getPosition()-sf::Vector2f(border_width/2,border_width/2));

    right = trapezium(texture_border, border_width, cloth_height);
    right.setOrigin(right.getOrigin() + sf::Vector2f((border_width+cloth_height)/2,border_width/2));
    right.rotate(90);
    right.setOrigin(right.getOrigin() + sf::Vector2f(-(border_width+cloth_height)/2,border_width/2));
    right.setPosition(cloth.getPosition()-sf::Vector2f(border_width/2-cloth_width,border_width/2));

    cor_tl = CornerShape(sf::Vector2f(border_width,border_width/2), 0, 180);
    cor_tl.setTexture(&texture_corner);
    cor_tl.setPosition(up.getPosition() + sf::Vector2f(border_width+border_width/4, border_width+border_width/4));
    cor_tl.rotate(45);

    cor_tr = CornerShape(sf::Vector2f(border_width,border_width/2), 0, 180);
    cor_tr.setTexture(&texture_corner);
    cor_tr.setPosition(up.getPosition() + sf::Vector2f(cloth_width-border_width/4, border_width+border_width/4));
    cor_tr.rotate(135);

    cor_bl = CornerShape(sf::Vector2f(border_width,border_width/2), 0, 180);
    cor_bl.setTexture(&texture_corner);
    cor_bl.setPosition(up.getPosition() + sf::Vector2f(border_width+border_width/4, cloth_height-border_width/4));
    cor_bl.rotate(-45);

    cor_br = CornerShape(sf::Vector2f(border_width,border_width/2), 0, 180);
    cor_br.setTexture(&texture_corner);
    cor_br.setPosition(up.getPosition() + sf::Vector2f(cloth_width-border_width/4, cloth_height-border_width/4));
    cor_br.rotate(-135);

    cor_tm = CornerShape(sf::Vector2f(border_width,border_width/2), 0, 170);
    cor_tm.setTexture(&texture_corner);
    cor_tm.setPosition(up.getPosition() + sf::Vector2f(cloth_width/2, border_width));
    cor_tm.rotate(90);

    cor_bm = CornerShape(sf::Vector2f(border_width,border_width/2), 0, 170);
    cor_bm.setTexture(&texture_corner);
    cor_bm.setPosition(up.getPosition() + sf::Vector2f(cloth_width/2, cloth_height));
    cor_bm.rotate(-90);
}

void Table::draw(sf::RenderWindow& window){
    window.draw(cloth);
    window.draw(up);
    window.draw(down);
    window.draw(left);
    window.draw(right);
    window.draw(cor_tl);
    window.draw(cor_tr);
    window.draw(cor_bl);
    window.draw(cor_br);
    window.draw(cor_tm);
    window.draw(cor_bm);
}
