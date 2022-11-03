#include "Objeto.h"

Objeto::Objeto()
{
    _texture.loadFromFile("sprite_sheets.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({2,33,33,22});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height);

    //ctor
}

void Objeto::update()
{

}

void Objeto::draw(sf::RenderTarget& target,sf::RenderStates states)const
{

}
