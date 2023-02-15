#include "Puerta.h"

Puerta::Puerta()
{
    //ctor
    _texture.loadFromFile("PUERTA.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0,0,36,30});

    _estado=false;

}

void Puerta::update(int cantE)
{
    if(cantE<=0)
    {
        _estado=true;
    }

}

void Puerta::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

sf::FloatRect Puerta::getBounds() const//obtiene coordenadas de los buffos
{                                          //para saber si colisiona
    return _sprite.getGlobalBounds();
}

void Puerta::respawn()
{
    _sprite.setPosition((float)_posicion.x*35,(float)_posicion.y*30);
}

