#pragma once
#include "corner.hpp"
#include "utils.hpp"

class Table{

    private:

        sf::RectangleShape cloth;
        sf::ConvexShape up;
        sf::ConvexShape down;
        sf::ConvexShape left;
        sf::ConvexShape right;
        CornerShape cor_tl, cor_tr, cor_bl, cor_br, cor_tm, cor_bm, cor;

    public:

        Table(const sf::Texture& texture_cloth, const sf::Texture& texture_border,
            const sf::Texture& texture_corner,
            double border_width, double cloth_width, double cloth_height,
            double WIDTH, double HEIGHT);

        void draw(sf::RenderWindow& window);

        bool entered_hole(sf::Vector2f pos, double rad);

};