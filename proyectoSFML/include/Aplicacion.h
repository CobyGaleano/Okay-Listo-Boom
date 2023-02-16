#ifndef APLICACION_H
#define APLICACION_H
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "MainMenu.h"
#include "Gameplay.h"
#include "Ranking.h"



class Aplicacion
{
    private:
        sf::RenderWindow* _window;
        sf::RenderTarget* _target;
        sf::RenderStates* _state;
        sf::Event* _evento;
        sf::Vector2u _resolucion;

        MainMenu _menu;

        Gameplay* gamePlay;

        Ranking* _ranking;

        bool gameOver=false;

        string _nombre;

    public:
        Aplicacion(sf::Vector2u resolucion);
        ~Aplicacion();
        string cargarNombre();



};

#endif // APLICACION_H
