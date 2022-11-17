#ifndef VIDA_H
#define VIDA_H
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <sstream> ///libreria para pasar de int a string la cantidad de vidas

class Vida : public sf::Drawable
{
    public:
        Vida();
        Vida(sf::RenderWindow &ventana);
        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
        void setVidas(int c);

        bool guardarVida();
        bool cargarVida(int pos);


    private:
        string _cantidad;

        sf::Sprite _sprite;
        sf::Texture _text;
        sf::Text _texto;
        sf::Vector2f _pos;
        sf::Font _font;
        sf::RenderWindow* _ventana;


};

#endif // VIDA_H
