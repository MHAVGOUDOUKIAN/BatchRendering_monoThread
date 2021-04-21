#include "SolidManager.hpp"
#include <iostream>

SolidManager::SolidManager(const int nb_Forme) : 
    listVertex(sf::Quads, 4), 
    nbFormeMax(nb_Forme)
{
    listVertex.resize(nb_Forme*4);
    listSolid.reserve(nb_Forme);

    for(int i=0; i < nb_Forme; ++i)
    {
        listSolid.emplace_back(0,0,0,i,true);

        listVertex[listSolid[i].indiceVertex*4].color = listSolid[i].m_color;
        listVertex[listSolid[i].indiceVertex*4+1].color = listSolid[i].m_color;
        listVertex[listSolid[i].indiceVertex*4+2].color = listSolid[i].m_color;
        listVertex[listSolid[i].indiceVertex*4+3].color = listSolid[i].m_color;
    }
}

void SolidManager::add(const float x, const float y, const float taille)
{

    unsigned int i=0;
    while(i < nbFormeMax-1 && !listSolid[i].dead)
    {
        ++i;
    }

    unsigned int e = listSolid[i].indiceVertex;
    if(listSolid[i].dead) // ON en remplace un
    {
        listSolid.erase(listSolid.begin()+i);
        listSolid.emplace_back(x,y,taille, e);
    } 

    ++nb_forme;
}

void SolidManager::add(const sf::Vector2f pos, const float taille)
{
    unsigned int i=0;
    while(i < nbFormeMax-1 && !listSolid[i].dead)
    {
        ++i;
    }

    if(listSolid[i].dead) // ON en remplace un
    {
        listSolid.erase(listSolid.begin()+i);
        listSolid.emplace_back(pos.x,pos.y, taille, i );
    }
    ++nb_forme;
}

void SolidManager::update(sf::Time deltaTime)
{
    for(size_t i=0; i < listSolid.size(); ++i)
    {
        if(!listSolid[i].dead) listSolid[i].update(deltaTime);
    }
    timeElapsed = clock.restart();
}

void SolidManager::render()
{
    sf::Clock clock;
    sf::Time timeElapsed;
    for(unsigned int i=0; i < nbFormeMax; ++i) {
        if(!listSolid[i].dead) {
            listVertex[listSolid[i].indiceVertex*4].position = sf::Vector2f(listSolid[i].pos.x+listSolid[i].taille, listSolid[i].pos.y-listSolid[i].taille);
            listVertex[listSolid[i].indiceVertex*4+1].position = sf::Vector2f(listSolid[i].pos.x+listSolid[i].taille, listSolid[i].pos.y+listSolid[i].taille);
            listVertex[listSolid[i].indiceVertex*4+2].position = sf::Vector2f(listSolid[i].pos.x-listSolid[i].taille, listSolid[i].pos.y+listSolid[i].taille);
            listVertex[listSolid[i].indiceVertex*4+3].position = sf::Vector2f(listSolid[i].pos.x-listSolid[i].taille, listSolid[i].pos.y-listSolid[i].taille);
        }
        else {
            listVertex[listSolid[i].indiceVertex*4].position = sf::Vector2f(0,0);
            listVertex[listSolid[i].indiceVertex*4+1].position = sf::Vector2f(0,0);
            listVertex[listSolid[i].indiceVertex*4+2].position = sf::Vector2f(0,0);
            listVertex[listSolid[i].indiceVertex*4+3].position = sf::Vector2f(0,0);
        }
    }
    timeElapsed = clock.restart();
    std::cout << timeElapsed.asSeconds()<< std::endl;
}

void SolidManager::draw(sf::RenderWindow& target)
{
    render();
    target.draw(listVertex);
}

void SolidManager::afficher()
{   
    system("clear");
    for(unsigned int i=0; i < nbFormeMax; ++i)
    {   
        std::cout << "Correspondance tablVertex: " << listSolid[i].indiceVertex << std::endl;
        std::cout << listSolid[i].pos.x << " / " << listSolid[i].pos.y << std::endl;
        std::cout << listSolid[i].dead << std::endl;
    }
}

SolidManager::~SolidManager() {}