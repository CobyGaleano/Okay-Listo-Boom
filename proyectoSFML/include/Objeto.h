#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics.hpp>


class Objeto: public sf::Drawable
{
    public:
        Objeto();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
};

#endif // OBJETO_H
