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
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        int _cantB=0;
        Bloques * _vBloques;
        sf::RenderWindow * _ventana;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
        for(int i=0;i<_cantB;i++){
            _ventana->draw(_vBloques[i]);
        }
        }
    public:
        Mapa(sf::RenderWindow &window);
        void mostrar();
        ~Mapa();

};

#endif // MAPA_H
