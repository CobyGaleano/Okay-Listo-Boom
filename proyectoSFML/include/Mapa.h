#ifndef MAPA_H
#define MAPA_H

#define CANT_FILAS 15
#define CANT_COLUMNAS 15

#include <iostream>
using namespace std;
#include "../Librerias.h"
#include <SFML/Graphics.hpp>
#include "Bloques.h"
#include "Buffos.h"
#include "Puerta.h"
class Mapa : public sf::Drawable, public sf::Transformable
{
    private:
        sf::RenderWindow * _ventana;
        int _matriz[CANT_COLUMNAS][CANT_FILAS];
        int _matrizPosiciones[CANT_COLUMNAS][CANT_FILAS];
        Buffos* _buffo1;
        Puerta* _puerta1;
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        int _cantB=0;
        Bloques * _vBloques;


        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            ///Dibuja el fondo verde
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &m_tileset;

            // draw the vertex array
            target.draw(m_vertices, states);

            ///SE DIBUJAN EL BUFFO Y LA PUERTA
            if(_buffo1->getEstado()){
                _ventana->draw(*_buffo1);
            }
            _ventana->draw(*_puerta1);
            ///Dibuja los bloques
            for(int i=0;i<_cantB;i++){
                if(_vBloques[i].getEstado()==true){
                    _ventana->draw(_vBloques[i]);
                }
            }
        }



    public:
        Mapa();
        Mapa(sf::RenderWindow &window);
        void mostrar();
        void copiarMatriz();
        void update();

        int getCantBloques();
        Bloques* getBloque(int pos);

        Buffos* getbuffo(){return _buffo1;}
        Puerta* getPuerta(){return _puerta1;}

        sf::Vector2f posicionarEnemigos(int cantE);
        sf::Vector2f posicionarPuerta();
        sf::Vector2f posicionarBuffo();


        bool cargarMapa(int pos);
        bool guardarMapa();

        ~Mapa();

};

#endif // MAPA_H
