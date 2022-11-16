#ifndef APLICACION_H
#define APLICACION_H
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "Mapa.h"
#include "Bloques.h"
#include "Bomba.h"
#include "Explosion.h"
#include "Vida.h"

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
        Vida* _vidasPJ;

        sf::Vector2f posAnteriorPJ;
        int _contPasos;
        int _cantE;///cant de enemigos
        Enemigo* _vEnemigos;
        sf::Vector2f* posAnteriorEnemigo;

        Mapa * _mapa;
        Bloques * _bloque;
        int _cantBloques;

        Bomba *_bomba;
        Explosion *_explosion;
        bool _bombaActiva;

        bool gameOver=false;
    public:
        Aplicacion(sf::Vector2u resolucion);
        ~Aplicacion();

        void iniciar(); ///inicializar variables y otros elementos
        void renderizar(); ///dibujar en pantalla los elementos del juego
        void procesar_logic();///logicas del juego
        void procesar_eventos();///teclado
        void gameLoop();

        void chequearColisionPJ();
        void chequearColisionExplosion();
        void chequearColisionEnemigo();

        int getCantEnemigos();
        int getCantBombas();
    protected:

};

#endif // APLICACION_H
