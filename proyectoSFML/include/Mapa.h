#ifndef MAPA_H
#define MAPA_H

#define CANT_FILAS 15
#define CANT_COLUMNAS 15

#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "Bloques.h"

class Mapa : public sf::Drawable, public sf::Transformable
{

    private:
        int _matriz[CANT_COLUMNAS][CANT_FILAS];
        int _matrizPosiciones[CANT_COLUMNAS][CANT_FILAS];
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        int _cantB=0;
        Bloques * _vBloques;
        sf::RenderWindow * _ventana;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            ///Dibuja el fondo verde
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &m_tileset;

            // draw the vertex array
            target.draw(m_vertices, states);

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


        sf::Vector2f posicionarEnemigos(int cantE);
        sf::Vector2f posicionarPuerta();
        sf::Vector2f posicionarBuffo();


        bool cargarMapa(int pos);
        bool guardarMapa();

        ~Mapa();

};

#endif // MAPA_H
