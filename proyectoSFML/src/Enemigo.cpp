#include "Enemigo.h"

Enemigo::Enemigo()
{
    _estado=true;
    _frame=0;
    _velocity={1,0};
    _timeMoov=0;
    _moovSelect=std::rand()%4+1;
    if(!_text.loadFromFile("sprite_sheets3.png")){
       cout << "ERROR LEER SPRITE ENEMIGOS" <<endl;
    }
    _sprite.setTexture(_text);
    _sprite.setTextureRect({5,204,20,18});
    //_sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    //_sprite.setPosition(sf::Vector2f(float(std::rand()%5+35),float(std::rand()%5+30)));
    _sprite.setScale(1.6f,1.6f);
    //ctor
}

void Enemigo::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

void Enemigo::update()
{
    _timeMoov+=1;
    _timeRespawn --;
    switch(_moovSelect)
    {
        case 1:
        {
            _velocity={1,0};
        }
    break;
        case 2:
        {
            _velocity={-1,0};
        }
    break;
        case 3:
        {
            _velocity={0,1};
        }
    break;
        case 4:
        {
            _velocity={0,-1};
        }
}
    if(_timeMoov>=150)
    {
        _moovSelect=std::rand()%4+1;
        _timeMoov=0;
    }
    if(_timeRespawn<0)
    {
        _newPosition={std::rand()%525+_sprite.getGlobalBounds().width,std::rand()%450+_sprite.getGlobalBounds().height};
    }

    _frame+=0.05;

    if (_frame>3){
        _frame=0;
    }
    _sprite.setTextureRect({5+int(_frame)*24,207,20,18});
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

bool Enemigo::guardarEnemigo(int pos){
    FILE *p;
    p=fopen("Enemigo.dat","rb+");
    if(p==NULL) return false;
    fseek(p, pos * sizeof(Enemigo), 0);
    bool escribio=fwrite(this, sizeof (Enemigo), 1, p);
    fclose(p);
    return escribio;
}
bool Enemigo::cargarEnemigo(int pos){
    FILE *p;
    p=fopen("Enemigo.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Enemigo), 0);
    bool leyo = fread(this, sizeof (Enemigo), 1, p);
    fclose(p);
    return leyo;
}
