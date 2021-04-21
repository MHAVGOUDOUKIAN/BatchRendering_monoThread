#ifndef SOLIDMANAGER_HPP_INCLUDED
#define SOLIDMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <tuple>
#include <vector>
#include "Solid.hpp"

class SolidManager
{
    public:
        SolidManager(const int nb_Forme);
        ~SolidManager();

        void add(const float x, const float y, const float taille);
        void add(const sf::Vector2f pos, const float taille);
        void update(sf::Time deltaTime);
        void render();
        void draw(sf::RenderWindow& target);

        void afficher();

        sf::VertexArray listVertex;
        std::vector<Solid> listSolid;
        unsigned int nbFormeMax;
        int nb_forme=0;

    private:
};

#endif //SOLIDMANAGER_HPP_INCLUDED