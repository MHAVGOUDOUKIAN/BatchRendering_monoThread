#ifndef SOLID_HPP_INCLUDED
#define SOLID_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include  "inline.h"

class Solid
{
    public:
        Solid(const float x, const float y, const float taille, const int indiceVErtex, const bool isDead = false);
        Solid(const sf::Vector2f pos, const float taille, const int indiceVErtex, const bool isDead = false);
        Solid(const Solid& forme);
        ~Solid();

        void update (sf::Time deltaTime);

        unsigned int indiceVertex;
        float taille;
        sf::Vector2f pos, vit;
        bool dead;
        sf::Color m_color;

        sf::Vector2f posInit, vitInit;
        float timeElapsedJump;
        float radiusInit ,masse;

    private:
};

#endif //SOLID_HPP_INCLUDED