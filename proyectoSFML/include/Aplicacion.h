#ifndef APLICACION_H
#define APLICACION_H
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "Mapa.h"
#include <ctime>
class Aplicacion
{
    private:
        sf::RenderWindow* _window;
        sf::RenderTarget* _target;
        sf::RenderStates* _state;
        sf::Event* _evento;
        MainMenu _menu;
        Personaje* _pj;
        int _cantE;///cant de enemigos
        Enemigo* _vEnemigos;
        Mapa * _mapa;
        bool gameOver=false;
    public:
        Aplicacion(sf::Vector2u resolucion);
        ~Aplicacion();

        void iniciar(); ///inicializar variables y otros elementos
        void renderizar(); ///dibujar en pantalla los elementos del juego
        void procesar_logic();///logicas del juego
        void procesar_eventos();///teclado
        void gameLoop();

        int getCantEnemigos();
    protected:

};

#endif // APLICACION_H
