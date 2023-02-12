#include "Explosion.h"

Explosion::Explosion()
{
    //_posicion={0,0};
    _frame=0;
    _tiempo=5;
    /*_texture.loadFromFile("fuego.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0,0,79,79});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    */

    ///FUEGO HORIZONTAL
    _texture.loadFromFile("Fuego_Largo.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({1,1,80,17});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);

    _explosion=false;

}

void Explosion::update()
{
    if(_explosion==true)
    {
        _frame+=0.15;
        _sprite.setTextureRect({5+int(_frame)*80,2,79,17});
        _sprite.setPosition(_posicion);
        if(_frame>=5)
        {
            _frame=0;
            _explosion=false;
        }
    }
}

Explosion::~Explosion(){
}

void Explosion::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

sf::FloatRect Explosion::getBounds() const //obtiene coordenadas de la explosion
{                                          //para saber si colisiona
    return _sprite.getGlobalBounds();
}

