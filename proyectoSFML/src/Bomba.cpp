#include "Bomba.h"

Bomba::Bomba()
{
    _frame=0;
    _tiempo=120;
    _estado=false;
    _explosion=false;

    buffer.loadFromFile("bomba.wav");
    sound.setBuffer(buffer);

    _texture.loadFromFile("sprite_sheets3.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({119,165,16,16});
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    _sprite.setScale(1.5,1.5);

    //ctor
}

void Bomba::update()
{
    if(_estado==true)
    {
        _frame+=0.10;
        if (_frame>3){_frame=0;}
        _sprite.setTextureRect({119+int(_frame)*23,165,16,16});
        _sprite.setPosition(_posicion);
        _tiempo-=1;
    }

    if(_tiempo<=0)
    {
        _explosion=true;
        _estado=false;
        _tiempo=120;
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

bool Bomba::guardarBomba(){
    FILE *p;
    p=fopen("Bomba.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Bomba), 1, p);
    fclose(p);
    return escribio;
}
bool Bomba::cargarBomba(int pos){
    FILE *p;
    p=fopen("Bomba.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Bomba), 0);
    bool leyo = fread(this, sizeof (Bomba), 1, p);
    fclose(p);
    return leyo;
}

void Bomba::sonido(){
    sound.play();
    sound.setVolume(4);
}
