#ifndef MAPA_H
#define MAPA_H

#define CANT_FILAS 15
#define CANT_COLUMNAS 15

#include "Personaje.h"

class Mapa : public sf::Drawable, public sf::Transformable
{

    private:
        //BloqueDes   _bd;
        //BloqueInd   _bi;
        int _matriz[CANT_COLUMNAS][CANT_FILAS];
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
        }
    public:
        Mapa();
        void mostrar();
        ~Mapa();

};

#endif // MAPA_H
