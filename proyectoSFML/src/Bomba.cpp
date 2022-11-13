#include "Bomba.h"

Bomba::Bomba()
{
    _texture.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({119,164,10,22});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);

    //ctor
}

void Bomba::update()
{

}

void Bomba::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

