#include <SFML/Graphics.hpp>
//fonction creer un rectangle
sf::RectangleShape PB_rect(int posX, int posY, int width, int height)
{
    //on cree le rectangle
    sf::RectangleShape rect(sf::Vector2f(width, height));
    //on donne une position
    rect.setPosition(posX, posY);
    //couleur principale
    rect.setFillColor(sf::Color(255, 0, 0, 255));
    return rect;
}
