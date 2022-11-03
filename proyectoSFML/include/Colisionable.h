#ifndef COLISIONABLE_H
#define COLISIONABLE_H

#include <SFML/Graphics.hpp>


class Colisionable
{
    public:
        Colisionable();
        virtual sf::FloatRect getBounds()const =0;
        bool siColisiona(Colisionable &col)const;


    private:

};

#endif // COLISIONABLE_H
