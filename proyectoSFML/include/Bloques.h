#ifndef BLOQUES_H
#define BLOQUES_H

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
#include "Colisionable.h"



class Bloques : public sf::Drawable, public sf::Transformable, public Colisionable
{

    private:
        int _tipo; ///1 no destruible - 2 destruible
        bool _estado; ///true activo - false inactivo
        sf::VertexArray m_vertices;
        sf::Texture _text;
        sf::Vector2f _pos;
        sf::Sprite _sprite;
    public:
        Bloques();
        void armar(int t, sf::Vector2f pos);
        void destruir();

        bool getEstado();
        sf::Vector2f getPos();

        int getTipo();

        void draw(sf::RenderTarget& target,sf::RenderStates states)const;

        sf::FloatRect getBounds() const override; ///colision
        bool guardarBloques(int pos);
        bool cargarBloques(int pos);
};

#endif // BLOQUES_H
