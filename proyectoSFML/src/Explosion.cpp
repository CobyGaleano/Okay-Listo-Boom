#include "Explosion.h"

Explosion::Explosion()
{
    _frame=0;
    _tiempo=5;
    _explosion=false;
    _texture.loadFromFile("fuego.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0,0,79,79});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    //ctor
}

void Explosion::update()
{
    if(_explosion==true)
    {
        _frame+=0.02;
        _sprite.setTextureRect({0+int(_frame)*83,0,79,79});
        _sprite.setPosition(_posicion);
    }
    if(_frame>=4)
    {
        _frame=0;
        _explosion=false;
    }
}

Explosion::~Explosion(){
}

void Explosion::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

sf::FloatRect Explosion::getBounds() const //obtiene coordenadas de personaje
{                                          //para saber si colisiona
    return _sprite.getGlobalBounds();
}
