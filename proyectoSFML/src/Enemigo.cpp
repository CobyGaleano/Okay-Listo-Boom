#include "Enemigo.h"

Enemigo::Enemigo()
{
    _frame=0;
    _velocity={0.23,-0.5};
    _text.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_text);
    _sprite.setTextureRect({7,209,17,22});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    //ctor
}

void Enemigo::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

void Enemigo::update()
{
    _frame+=0.033;

    if (_frame>3){
        _frame=0;
    }
    _sprite.setTextureRect({7+int(_frame)*24,209,17,22});
    _sprite.move(_velocity);

    ///evitar que se vaya de la pantalla
     if(_sprite.getGlobalBounds().left<0)
        {
            _sprite.setPosition(_sprite.getOrigin().x,_sprite.getPosition().y);
        }

        if(_sprite.getGlobalBounds().top<0)
        {
            _sprite.setPosition(_sprite.getPosition().x,_sprite.getOrigin().y);
        }

        if(_sprite.getGlobalBounds().left+_sprite.getGlobalBounds().width>525)
        {
            _sprite.setPosition(525-(_sprite.getGlobalBounds().width-_sprite.getOrigin().x),_sprite.getPosition().y);
        }

        if(_sprite.getGlobalBounds().top+_sprite.getGlobalBounds().height>450)
        {
            _sprite.setPosition(_sprite.getPosition().x,450-(_sprite.getGlobalBounds().height-_sprite.getOrigin().y));
        }
}

void Enemigo::respawn() ///respawn del enemigo (aleatorio)
{
    _sprite.setPosition(std::rand()%700+_sprite.getGlobalBounds().width,std::rand()%500+_sprite.getGlobalBounds().height);
}

sf::FloatRect Enemigo::getBounds() const
{
    return _sprite.getGlobalBounds();
}
