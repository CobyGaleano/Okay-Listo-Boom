#ifndef APLICACION_H
#define APLICACION_H
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "MainMenu.h"
#include "Gameplay.h"

class Aplicacion
{
    private:
        sf::RenderWindow* _window;
        sf::RenderTarget* _target;
        sf::RenderStates* _state;
        sf::Event* _evento;

        MainMenu _menu;

        Gameplay* gamePlay;

        bool gameOver=false;
    public:
        Aplicacion(sf::Vector2u resolucion);
        ~Aplicacion();

};

#endif // APLICACION_H
