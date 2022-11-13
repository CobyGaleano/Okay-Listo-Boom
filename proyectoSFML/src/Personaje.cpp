#include "Personaje.h"

Personaje::Personaje()
{
    _frame=0;
    _velocity={2,2};
    _texture.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({20,130,18,21});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height);
    //ctor
}

void Personaje::update()
{
        switch(_state)
        {
    case PersonajeState::Idle://si el personaje no se mueve carga dicha textura
        {
            _sprite.setTextureRect({20,130,18,21});
        }
        break;
    case PersonajeState::m_up:
        {
            ///cambio sprite
            _frame +=0.05;

            if(_frame>=3)
            {
            _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,76,20,21});
            _sprite.move(_movePosition);


            }
        break;
    case PersonajeState::m_down:
        {
            ///cambio sprite
            _frame +=0.05;

            if(_frame>=3)
            {
                _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,130,20,21});
            _sprite.move(_movePosition);


        }
        break;
    case PersonajeState::m_left:
        {
            ///cambio sprite
            _frame +=0.05;

            if(_frame>=3)
            {
                _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,103,20,21});
            _sprite.move(_movePosition);

            if(_movePosition.x<0)///que mire hacia donde corre
            {
                _sprite.setScale(1,1);
            }
            else if(_movePosition.x>0)
            {
                _sprite.setScale(-1,1);
            }
        }
        break;
    case PersonajeState::m_right:
        {
            ///cambio sprite
            _frame +=0.05;

            if(_frame>=3)
            {
                _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,103,20,21});
            _sprite.move(_movePosition);

            if(_movePosition.x<0)  ///que mire hacia donde corre
            {
                _sprite.setScale(1,1);
            }
            else if(_movePosition.x>0)
            {
                _sprite.setScale(-1,1);
            }
        }
        break;
        }

        ///evitar que se vaya de la pantalla
        if(_sprite.getGlobalBounds().left<0)  //izquierda
        {
            _sprite.setPosition(_sprite.getOrigin().x,_sprite.getPosition().y);
        }

        if(_sprite.getGlobalBounds().top<0) //arriba
        {
            _sprite.setPosition(_sprite.getPosition().x,_sprite.getOrigin().y);
        }

        if(_sprite.getGlobalBounds().left+_sprite.getGlobalBounds().width>525)//derecha
        {
            _sprite.setPosition(525-(_sprite.getGlobalBounds().width-_sprite.getOrigin().x),_sprite.getPosition().y);
        }

        if(_sprite.getGlobalBounds().top+_sprite.getGlobalBounds().height>450) //abajo
        {
            _sprite.setPosition(_sprite.getPosition().x,450-(_sprite.getGlobalBounds().height-_sprite.getOrigin().y));
        }
}

void Personaje::cmd()//controlador del personaje
{
    _movePosition= {0,0};
    _state=PersonajeState::Idle;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _movePosition.y=-_velocity.y;
            _state=PersonajeState::m_up;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _movePosition.x=-_velocity.x;
            _state=PersonajeState::m_left;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _movePosition.y=_velocity.y;
            _state=PersonajeState::m_down;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _movePosition.x=_velocity.x;
            _state=PersonajeState::m_right;
        }
}

void Personaje::draw(sf::RenderTarget& target,sf::RenderStates states)const //enseña a window como dibujar
{                                                                           //un personaje
    target.draw(_sprite,states);
}

sf::FloatRect Personaje::getBounds() const //obtiene coordenadas de personaje
{                                          //para saber si colisiona
    return _sprite.getGlobalBounds();
}

void Personaje::muere()
{
    while(_frame<7)
    {
    _frame+=0.25;

    _sprite.setTextureRect({72+int(_frame)*14,41,14,20});
    _sprite.setPosition(1,1);
    }

}

