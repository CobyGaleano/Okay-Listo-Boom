#ifndef BOMBA_H
#define BOMBA_H
#include "../Librerias.h"

class Bomba: public sf::Drawable
{
    public:
        Bomba();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void respawn();

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;

};

#endif // BOMBA_H
