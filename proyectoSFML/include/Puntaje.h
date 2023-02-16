#ifndef PUNTAJE_H
#define PUNTAJE_H
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <sstream> ///libreria para pasar de int a string la cantidad puntos

class Puntaje : public sf::Drawable
{
    public:
        Puntaje();
        Puntaje(sf::RenderWindow &ventana);
        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
        void setPuntaje(int c);

        bool guardarPuntaje();
        bool cargarPuntaje(int pos);

        string getPuntaje();


    private:
        string _cantidad;

        sf::Sprite _sprite;
        sf::Texture _text;
        sf::Text _texto;
        sf::Vector2f _pos;
        sf::Font _font;
        sf::RenderWindow* _ventana;
};

#endif // PUNTAJE_H
