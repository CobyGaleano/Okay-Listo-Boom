#include "Personaje.h"

Personaje::Personaje(){
}

Personaje::Personaje(sf::RenderWindow &ventana)
{
    _ventana=&ventana;
    _cantVidas=3;
    _frame=0;
    _cantBombas=1;
    _puntaje=0;
    _chupoFernet=false;
    _pusoBomba=false;
    _muerto=false;
    _respawn=false;
    _velocity={2,2};
    ///cuando camina
    ///cuando planta
    bufferMuerte.loadFromFile("muere.wav");
    soundMuerte.setBuffer(bufferMuerte);
    ///sprite
    _texture.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({20,130,18,21});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    _sprite.setScale(1.44,1.3);
    _sprite.setPosition(sf::Vector2f(52.5,45));

    //ctor
}

void Personaje::update()
{
    switch(_state)
    {
    case PersonajeState::Idle://si el personaje no se mueve carga dicha textura
        {
            _sprite.setTextureRect({20,130,18,21});
            _sprite.setScale(1.44,1.3);

        }
        break;
    case PersonajeState::m_up:
        {
            ///cambio sprite
            _frame +=0.1;

            if(_frame>=3)
            {
            _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,76,20,21});
            _sprite.move(_movePosition);
            if(_frame>=2.5){sound.play();}


            }
        break;
    case PersonajeState::m_down:
        {
            ///cambio sprite
            _frame +=0.1;

            if(_frame>=3)
            {
                _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,130,18,21});
            _sprite.move(_movePosition);
            if(_frame>=2.5){sound.play();}

        }
        break;
    case PersonajeState::m_left:
        {
            ///cambio sprite
            _frame +=0.1;

            if(_frame>=3)
            {
                _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,103,18,21});
            _sprite.move(_movePosition);
            if(_frame>=2.5){sound.play();}

            if(_movePosition.x<0)///que mire hacia donde corre
            {
                _sprite.setScale(1.44,1.30);
            }
            else if(_movePosition.x>0)
            {
                _sprite.setScale(-1.44,1.30);
            }
        }
        break;
    case PersonajeState::m_right:
        {
            ///cambio sprite
            _frame +=0.1;

            if(_frame>=3)
            {
                _frame=0;
            }
            _sprite.setTextureRect({0+int(_frame)*20,103,18,21});
            _sprite.move(_movePosition);
            if(_frame>=2.5){sound.play();}

            if(_movePosition.x<0)  ///que mire hacia donde corre
            {
                _sprite.setScale(1.44,1.3);
            }
            else if(_movePosition.x>0)
            {
                _sprite.setScale(-1.44,1.30);
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

    if(_chupoFernet)
    {
        _cantBombas=4;
        _chupoFernet=false;
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

        ///soltar bomba
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            if(_cantBombas>0 && _pusoBomba==false){
                _cantBombas--;
                _pusoBomba=true;
                _posBomba=_sprite.getPosition();
            }
        }
}

void Personaje::draw(sf::RenderTarget& target,sf::RenderStates states)const //enseña a window como dibujar
//un personaje
{
    target.draw(_sprite,states);
}

sf::FloatRect Personaje::getBounds() const //obtiene coordenadas de personaje
{                                          //para saber si colisiona
    return _sprite.getGlobalBounds();
}

/*void Personaje::muere()
{
    soundMuerte.play();
    soundMuerte.setVolume(4);
    _frame +=0.2;

    if(_frame>=3)
    {
        _frame=0;
    }
    _sprite.setTextureRect({72+int(_frame)*16,41,15,21});
    cout<<endl<<"ENTRA A DIBUJAR";
}

void Personaje::respawn()
{
    _sprite.setPosition(50,50);
    _cantVidas--;
    if(_cantVidas<0){
        _cantVidas=0;
    }
    setMuerto(false);
    setRespawn(false);
}*/
void Personaje::muere()
{
    soundMuerte.play();
    soundMuerte.setVolume(4);
    while(_frame<7)
    {
        _frame+=0.25;

        _sprite.setTextureRect({72+int(_frame)*14,41,14,20});
    }
    _sprite.setPosition(52.5,45);
    _cantVidas--;
    if(_cantVidas<0){
        _cantVidas=0;
    }
}

void Personaje::setPos(sf::Vector2f pos){
    _sprite.setPosition(pos);
}

bool Personaje::guardarPersonaje(){
    FILE *p;
    p=fopen("Personaje.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Personaje), 1, p);
    fclose(p);
    return escribio;
}
bool Personaje::cargarPersonaje(int pos){
    FILE *p;
    p=fopen("Personaje.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Personaje), 0);
    bool leyo = fread(this, sizeof (Personaje), 1, p);
    fclose(p);
    return leyo;
}

Personaje::~Personaje(){
}
