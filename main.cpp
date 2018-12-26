#pragma region includes
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "shap.h"
#pragma endregion includes


#pragma region variables
sf::RenderWindow window;///LA DECLARATION D'UNE FENETRE
sf::RectangleShape rect;
sf::RectangleShape rect2;
int speed = 2;
sf::Vector2i PositionSouris;
sf::Texture perso;
sf::Sprite sprite_perso;
enum Dir{Down, Left, Right, Up};///L'INSTRUCTION ENUM POUR LA GESTION DES TOUCHES DU CLAVIER
sf::Vector2i anim(1, Right);///L'ANIMATION PAR DEFAUT EST Right
bool updateFPS = true;
int blockSize = 32;
sf::View view;
int const screenW = 800, screenH = 600;
#pragma endregion variables


#pragma region prototypes
void gestion_clavier();
void gestion_souris();
#pragma andregion prototypes

int main()
{
    /** CREATION DE LA FENETRE 800x600 PIXELS*/
    window.create(sf::VideoMode(800,600), "Rasam Legends");///LA CONSTRUCTION DE LA FENETRE

    /** MODIFIER LA POSITION DE LA FENETRE*/
    window.setPosition(sf::Vector2i(192, 0)); /** VECTOR 2i, VEUT DIRE LES DEUX AXES (X ET Y int)*/
    window.setFramerateLimit(50);///la création de 50 images par seconde

    std::cout << "Lancement du jeu" <<std::endl;

    rect = PB_rect(480,300,32,32);
    rect2 = PB_rect(1000,1000,32,32);

    /** LA DEFINITION DU COMPTEUR DE TEMPS PAR VITESSE*/

    sf::Clock time;

    /** LA CREATION D'UN PERSONNAGE ET
    LA DEFINITION DE SA TAILLE EN 32 PIXELS POUR QUE LA SPRITE NE DEPASSE PAS
    LE RECTAGLE CREE*/
    if (!perso.loadFromFile("ico.png"))
    {
        std::cout << "Erreur du chargement!" <<std::endl;
    }
    perso.setSmooth(true);

    sprite_perso.setTexture(perso);


    /** TANT QUE LA FENETRE EST OUVERTE...*/
    while(window.isOpen())
    {
        /** CREATION DES EVENNEMENTS (CLIQUE DE LA SOURIS, APPUIE SUR LE CLAVIER, OU LES JOYSTICKS)*/
        sf::Event event;

        /** TESTES DES EVENEMENTS*/
        while(window.pollEvent(event))
        {
            /** SI ON CLIQUE SUR FERMER*/
            if (event.type == sf::Event::Closed)
                window.close();/** ON FERME LA FENETRE*/

        /** SI ON APPUIE SUR UNE TOUCHE LE PERSONNAGE BOUGE, SINON CA FAIT RIEN */
        if(event.type == sf::Event::KeyPressed)
        {
            updateFPS = true;
        }
        else
        {
            updateFPS = false;
        }

        /** APPEL DE LA FONCTION GESTION DU CLAVIER*/
        gestion_clavier();

        /** APPEL DE LA FONCTION GESTION SOURIS*/
        gestion_souris();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            std::cout << "Vous avez appuyer sur la touche A" <<std::endl;
        }

        if(updateFPS == true)
        {
            if(time.getElapsedTime().asMilliseconds() >= 50)
            {
            anim.x--;
            if(anim.x * blockSize >= perso.getSize().x)
            anim.x = speed;
        time.restart();
                std::cout << sprite_perso.getPosition().x << "," << sprite_perso.getPosition().y <<std::endl;
            }
        }
        }

        /** DECOUPAGE DU PERSONNAGE */
        sprite_perso.setTextureRect(sf::IntRect(anim.x * blockSize, anim.y * blockSize, blockSize, blockSize));

        /** DETECTION DES COLLISIONS ENTRE LE PERSO ET LE RECT*/
        if((std::abs((sprite_perso.getPosition().x + 16) - (rect.getPosition().x + 16)) < blockSize) &&
           (std::abs((sprite_perso.getPosition().y + 16) - (rect.getPosition().y + 16)) < blockSize))
        {
            system("color d");
            std::cout<< "Collision !" <<std::endl;
            rect.setFillColor(sf::Color::Black);
            rect2.setFillColor(sf::Color::Black);
        }

        /** CREATION DE LA VUE
        ON CENTRE LA VUE SUR LE PERSO */
        view.reset(sf::FloatRect(0, 0, screenW, screenH));
        sf::Vector2f position(screenW / 2, screenH / 2); ///ON CENTRE LA VUE
        position.x = sprite_perso.getPosition().x + (blockSize / 2) - (screenW / 2);
        position.y = sprite_perso.getPosition().y + (blockSize / 2) - (screenH / 2);
        if (position.x < 0)
            position.x = 0;
        if (position.y < 0)
            position.y = 0;

        /** LA FONCTION DU MOUVEMENT DE LA CAMERA */
        view.reset(sf::FloatRect(position.x, position.y, screenW, screenH));

        window.setView(view);///L'AFFICHAGE DU MOUVEMENT DE LA CAMERA

        /** ON DESSINE, ON AFFICHE ET ON MET A JOUR*/
        window.draw(rect);///PERMET DE DESSINER A L'ECRAN CE QUE L'ON A CREE (LE RECTANGLE ROUGE)
        window.draw(rect2);
        window.draw(sprite_perso);/// IDEM...(LE PERSONNAGE)
        window.display();///PERMET D'AFFICHER LES ELEMENTS CREES
        window.clear();/** PERMET D'EFFACER LE 50 IMAGES PAR SECONDE ET CREER DE NOUVEAU
                        //UNE IMAGE POUR QUE LA SPRITE NE SE REPETE PLUSIEURS FOIS
                        //ET QUE CA NOUS PERMET DE VOIR UN PERSONNAGE OU DECORS BOUGENT */
    }

    return 0;
}
/** GESTION DU CLAVIER */
void gestion_clavier()
{

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            anim.y = Up;
            sprite_perso.move(0, -speed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            anim.y = Down;
            sprite_perso.move(0, speed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            anim.y = Left;
            sprite_perso.move(-speed, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            anim.y = Right;
            sprite_perso.move(speed, 0);
        }

        if(sprite_perso.getPosition().x <= 0)
            sprite_perso.setPosition(sf::Vector2f(0, sprite_perso.getPosition().y));

        if(sprite_perso.getPosition().y <= 0)
            sprite_perso.setPosition(sf::Vector2f(sprite_perso.getPosition().x, 0));
}
   /** GESTION SOURIS*/
    void gestion_souris()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            /** ON RECUPERE LES CORDONNE DE LA SOURIS*/
            PositionSouris = sf::Mouse::getPosition(window);
            std::cout << "Mouse.x "<< PositionSouris.x << " Mouse.y "<< PositionSouris.y <<std::endl;

            int mouseX = PositionSouris.x;
            int mouseY = PositionSouris.y;
            rect.setPosition(mouseX, mouseY); /** ON POSITIONNE LE RECT */
        }
    }
