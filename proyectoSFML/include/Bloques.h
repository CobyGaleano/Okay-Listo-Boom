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
        Bloques(int t, sf::Vector2f pos);
        void setEstado(bool es);
        sf::Vector2f getPos();
        sf::FloatRect getBounds() const override;
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;

};

#endif // BLOQUES_H
