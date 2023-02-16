#include "Buffos.h"

Buffos::Buffos()
{
    //ctor
    _texture.loadFromFile("FERNET.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0,0,34,29});

    bufferDaleBoca.loadFromFile("DaleBoca.wav");
    soundDaleBoca.setBuffer(bufferDaleBoca);

    _estado=true;
    _TocoBuffo=false;
   // _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
   // _sprite.setPosition(70,30);
}

Buffos& Buffos::getBuffo(){
    return *this;
}

void Buffos::update()
{
    if(_TocoBuffo==true)
    {
        soundDaleBoca.play();
        soundDaleBoca.setVolume(10);
    }

}

void Buffos::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}

sf::FloatRect Buffos::getBounds() const //obtiene coordenadas de los buffos//para saber si colisiona
{
    return _sprite.getGlobalBounds();
}

void Buffos::respawn()
{
    _sprite.setPosition((float)_posicion.x*35,(float)_posicion.y*30);
}
bool Buffos::guardarBuffos(){
    FILE *p;
    p=fopen("Buffos.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Buffos), 1, p);
    fclose(p);
    return escribio;
}
bool Buffos::cargarBuffos(int pos){
    FILE *p;
    p=fopen("Buffos.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Buffos), 0);
    bool leyo = fread(this, sizeof (Buffos), 1, p);
    fclose(p);
    return leyo;
}
