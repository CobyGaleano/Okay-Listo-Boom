#include "Bomba.h"

Bomba::Bomba()
{
    _frame=0;
    _tiempo=10;
    _estado=false;
    _explosion=false;
    _texture.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({119,165,26,43});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);


    //ctor
}

void Bomba::update()
{
    if(_estado==true)
    {
        _frame+=0.10;
        if (_frame>3){_frame=0;}
        _sprite.setTextureRect({114+int(_frame)*23,160,23,26});
        _sprite.setPosition(_posicion);
        _tiempo-=0.26;
    }

    if(_tiempo<=0)
    {
        _explosion=true;
        _estado=false;
        _tiempo=10;
    }

}

void Bomba::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

sf::FloatRect Bomba::getBounds() const //obtiene coordenadas de personaje
{                                          //para saber si colisiona
    return _sprite.getGlobalBounds();
}
