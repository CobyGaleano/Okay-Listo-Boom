#ifndef APLICACION_H
#define APLICACION_H
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "MainMenu.h"
#include "Gameplay.h"
#include "PantallaNivel.h"
#include "PantallaTemporal.h"

class Aplicacion
{
    private:
        sf::RenderWindow* _window;
        sf::RenderTarget* _target;
        sf::RenderStates* _state;
        sf::Event* _evento;

        MainMenu _menu;

        Gameplay* gamePlay;
        PantallaNivel* pantallaDelNivel;

        bool gameOver=false;

    public:
        Aplicacion(sf::Vector2u resolucion);
        ~Aplicacion();

};

#endif // APLICACION_H
