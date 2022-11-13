#include "Bomba.h"

Bomba::Bomba()
{
    _frame=0;
    _estado=false;
    _texture.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({114,160,23,26});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    _sprite.setPosition(-1,-1);

    //ctor
}

void Bomba::update()
{
    if(_estado==true)
    {
    _frame+=0.10;
    if (_frame>3){_frame=0;}
    _sprite.setTextureRect({114+int(_frame)*23,160,23,26});
    _sprite.setOrigin(_posicion);

    }

}

void Bomba::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}


