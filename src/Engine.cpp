#include <iostream>
#include "Engine.hpp"

Engine::Engine(): m_window(sf::VideoMode(700,700), "Application SFML"), slm(150000)
{
    TimePerFrame = sf::seconds(1.f/120.f);
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    if(!m_font.loadFromFile("assets/AldotheApache.ttf")) {
        std::cout << "Erreur: Impossible de charger la police" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(64);
    m_text.setFillColor(sf::Color::Red);
    m_text.setStyle(sf::Text::Regular);
    m_text.setPosition(5,5);
}

void Engine::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            processEvents();
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        render();
    }
}

void Engine::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
                
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;

            default:
                break;
        }
    }
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) {
        this-> Left = isPressed;
        if(!isPressed) { this->LeftPressed=false; }
    }
    if(key == sf::Keyboard::Right) {
        this-> Right = isPressed;
        if(!isPressed) { this->RightPressed=false; }
    }
    if(key == sf::Keyboard::Down) {
        this-> Down = isPressed;
        if(!isPressed) { this->DownPressed=false; }
    }
    if(key == sf::Keyboard::Up) {
        this-> Up = isPressed;
        if(!isPressed) { this->UpPressed=false; }
    }
    if(key == sf::Keyboard::Space) {
        this-> Space = isPressed;
        if(!isPressed) { this->SpacePressed=false; }
    }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { this-> MouseL = isPressed; }
    if(mouse == sf::Mouse::Right) {
        this-> MouseR = isPressed;
        if(!isPressed) { this->MouseRPressed=false; }
    }
}

void Engine::update(sf::Time deltaTime)
{
    //////////////////////////////////////////////////////////////
    ////////////// R�ponse aux inputs ////////////////////////////
    //////////////////////////////////////////////////////////////

    if(Echap) { m_window.close(); }
    if(MouseL) { }
    if(MouseR && !MouseRPressed) {}
    if(Left && !LeftPressed) { 
        slm.add(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,30);
        slm.add(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,40);
        slm.add(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,20);
        //LeftPressed=true;
    }
    if(Right && !RightPressed) { 
        for(unsigned int i=0; i < slm.nbFormeMax ; ++i)
        {
            slm.listSolid[i].dead=true;
        }
    }
    if(Up && !UpPressed) { }
    if(Down) {  }
    if(Space) { }


    //////////////////////////////////////////////////
    ////////////// Update ////////////////////////////
    //////////////////////////////////////////////////
    slm.update(deltaTime);

    m_text.setString(std::to_string(slm.nb_forme));
}

void Engine::render(void)
{
    m_window.clear();
    slm.draw(m_window);
    m_window.draw(m_text);
    m_window.display();
}

Engine::~Engine()
{}
