#ifndef BLOQUES_H
#define BLOQUES_H
#include "Mapa.h"
#include "Personaje.h"


class Bloques
{
    public:
        Bloques();
        void Bdestruible();
        void BnoDestruible();

    private:
        sf::Sprite _sprite;
        sf::Texture _text;


};

#endif // BLOQUES_H
