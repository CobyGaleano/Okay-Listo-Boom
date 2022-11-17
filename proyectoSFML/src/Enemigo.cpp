#include "Enemigo.h"

Enemigo::Enemigo()
{
    _frame=0;
    _velocity={2,0};
    _timeMoov=0;
    _moovSelect=std::rand()%4+1;
    _text.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_text);
    _sprite.setTextureRect({7,209,17,22});
    ///_sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    _sprite.setPosition(sf::Vector2f(float(std::rand()%5+35),float(std::rand()%5+30)));
    //ctor
}

void Enemigo::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

void Enemigo::update()
{
    _timeMoov+=0.15;
    _timeRespawn --;
    switch(_moovSelect)
    {
        case 1:
        {
            _velocity={3,0};
        }
    break;
        case 2:
        {
            _velocity={-3,0};
        }
    break;
        case 3:
        {
            _velocity={0,3};
        }
    break;
        case 4:
        {
            _velocity={0,-3};
        }
}
    if(_timeMoov>=15)
    {
        _moovSelect=std::rand()%4+1;
        _timeMoov=0;
    }
    if(_timeRespawn<0)
    {
        _newPosition={std::rand()%525+_sprite.getGlobalBounds().width,std::rand()%450+_sprite.getGlobalBounds().height};
    }

    _frame+=0.15;

    if (_frame>3){
        _frame=0;
    }
    _sprite.setTextureRect({7+int(_frame)*24,209,17,22});
    _sprite.move(_velocity);

    ///evitar que se vaya de la pantalla
     if(_sprite.getGlobalBounds().left<0)
        {
            //_sprite.setPosition(_sprite.getOrigin().x,_sprite.getPosition().y);
            _velocity.x=-_velocity.x;
        }

        if(_sprite.getGlobalBounds().top<0)
        {
           // _sprite.setPosition(_sprite.getPosition().x,_sprite.getOrigin().y);
           _velocity.y=-_velocity.y;
        }

        if(_sprite.getGlobalBounds().left+_sprite.getGlobalBounds().width>525)
        {
           // _sprite.setPosition(525-(_sprite.getGlobalBounds().width-_sprite.getOrigin().x),_sprite.getPosition().y);
           _velocity.x=-_velocity.x;
        }

        if(_sprite.getGlobalBounds().top+_sprite.getGlobalBounds().height>450)
        {
            //_sprite.setPosition(_sprite.getPosition().x,450-(_sprite.getGlobalBounds().height-_sprite.getOrigin().y));
            _velocity.y=-_velocity.y;
        }
}

void Enemigo::respawn(sf::Vector2f pos) ///respawn del enemigo (aleatorio)
{
    ///_sprite.setPosition(std::rand()%524+_sprite.getGlobalBounds().width,std::rand()%449+_sprite.getGlobalBounds().height);
    _sprite.setPosition((float)pos.x*35,(float)pos.y*30);
    _timeRespawn=60*3;
}

void Enemigo::setPos(sf::Vector2f p){
    _sprite.setPosition(p);
}

void Enemigo::damage()///acciones que realizar el enemigo al golpear
{
    ///respawn();
}

sf::FloatRect Enemigo::getBounds() const
{
    return _sprite.getGlobalBounds();
}
