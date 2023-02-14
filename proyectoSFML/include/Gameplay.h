#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "Personaje.h"
#include "Enemigo.h"
#include "Mapa.h"
#include "Bloques.h"
#include "Bomba.h"
#include "Explosion.h"
#include "Vida.h"
#include "Puntaje.h"


class Gameplay
{
    private:
        char _nombreUsuario[30];

        sf::RenderWindow* _window;
        sf::RenderTarget* _target;
        sf::RenderStates* _state;
        sf::Event* _evento;

        Personaje* _pj;
        Vida* _vidasPJ;
        Puntaje* _puntajePJ;
        sf::Vector2f posAnteriorPJ;
        int _contPasos;
        int _cantE;///cant de enemigos
        int _enemigosActivos;
        Enemigo* _vEnemigos;
        sf::Vector2f* posAnteriorEnemigo;

        Mapa * _mapa;
        Bloques * _bloque;
        int _cantBloques;

        Bomba *_bomba;
        Explosion *_explosion;
        bool _bombaActiva;

        bool gameOver=false;
        bool _levelUp=false;


    public:
        Gameplay();
        Gameplay(sf::Vector2u resolucion,sf::RenderWindow &window);
        void run(sf::Vector2u resolucion,sf::RenderWindow &window);
        ~Gameplay();

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

        bool guardarPartida();
        bool cargarPartida(int pos);

        bool cargarJuego();

        void setGameOver(bool go){gameOver=go;}

        bool getLevelUp();
};

#endif // GAMEPLAY_H
