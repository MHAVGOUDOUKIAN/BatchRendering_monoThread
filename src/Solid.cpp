#include "Solid.hpp"
#include <iostream>

#define g 10 * 150
#define h 5

Solid::Solid(const float x, const float y, const float taille, const int indiceVErtex, const bool isDead)
{
    this->indiceVertex = indiceVErtex;
    this->pos.x = x;
    this->pos.y = y;
    this->taille = taille;
    this->dead = isDead;
    m_color = sf::Color(randomi(0,255),randomi(0,255),randomi(0,255));
    this->vit.x = randomf(-500,500);
    this->vit.y = randomf(-500,500);
    posInit = sf::Vector2f(pos.x, pos.y);
    vitInit = sf::Vector2f(vit.x, vit.y);
    timeElapsedJump = 0;
    radiusInit=taille;
    masse=10;

}

Solid::Solid(const sf::Vector2f pos, const float taille, const int indiceVErtex, const bool isDead)
{
    this->indiceVertex = indiceVErtex;
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    this->taille = taille;
    this->dead = isDead;
    m_color = sf::Color(randomi(0,255),randomi(0,255),randomi(0,255));
    this->vit.x = randomf(-500,500);
    this->vit.y = randomf(-500,500);
    posInit = sf::Vector2f(pos.x, pos.y);
    vitInit = sf::Vector2f(vit.x, vit.y);
    timeElapsedJump = 0;
    radiusInit=taille;
    masse=10;
}

Solid::Solid(const Solid& forme)
{
    this->indiceVertex = forme.indiceVertex;
    this->pos.x = forme.pos.x;
    this->pos.y = forme.pos.x;
    this->taille = forme.taille;
    this->dead = forme.dead;
    m_color = sf::Color(randomi(0,255),randomi(0,255),randomi(0,255));
    this->vit.x = forme.vit.x;
    this->vit.y = forme.vit.y;
    posInit = sf::Vector2f(pos.x, pos.y);
    vitInit = sf::Vector2f(vit.x, vit.y);
    timeElapsedJump = 0;
    radiusInit=taille;
    masse=10;
}

Solid::~Solid()
{}

void Solid::update(sf::Time deltaTime)
{
    timeElapsedJump += deltaTime.asSeconds();

    vit.y = (-1) * g * timeElapsedJump + vitInit.y;
    //m_vit.x = m_vitInit.x; // Cas sans frottements
    vit.x = vitInit.x * exp((-h*timeElapsedJump)/masse); // Cas avec frottements de (air)

    pos.y = -((-0.5) * g * timeElapsedJump * timeElapsedJump + vitInit.y * timeElapsedJump) + posInit.y;
    //m_pos.x = m_vitInit.x * m_timeElapsedJump + m_posInit.x; // Cas sans frottements
    pos.x = (masse/h) * vitInit.x * (1-exp(-h * timeElapsedJump / masse)) + posInit.x; // Cas avec frottements (air)

    if(pos.y - taille < 0) {
        pos.y = taille;
        vit.y = vit.y*(-1);
    }
    else if(pos.y + taille > 700) {
        if(vit.y > 0 && vit.y < 5) {// Cas ou la balle ne rebondit plus
            pos.y = 700-taille;
            vit.y = 0;
        }
        else { // Cas du rebond
            pos.y = 700-taille;
            vit.y = vit.y*(-1) * 0.65 /* Facteur d'Adhérence du sol */;
        }
    }

    if(pos.x - taille < 0) {
        pos.x = taille;
        vit.x = vit.x * (-1);
    } // Rebond sur les cotés
    else if(pos.x + taille > 700) {
        pos.x = 700-taille;
        vit.x = vit.x * (-1);
    }
    if(abs(vit.x) < 10) {
        vit.x = 0;
    }

    pos = sf::Vector2f(pos.x,pos.y);
    posInit = pos;

    vit = sf::Vector2f(vit.x,vit.y);
    vitInit = vit;

    timeElapsedJump = 0;
}