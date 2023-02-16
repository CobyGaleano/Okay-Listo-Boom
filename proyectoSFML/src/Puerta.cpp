#include "Puerta.h"

Puerta::Puerta()
{
    //ctor
    _texture.loadFromFile("PUERTA.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0,0,34,29});

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

Puerta& Puerta::getPuerta(){
    return *this;
}
bool Puerta::guardarPuerta(){
    FILE *p;
    p=fopen("Puerta.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Puerta), 1, p);
    fclose(p);
    return escribio;
}
bool Puerta::cargarPuerta(int pos){
    FILE *p;
    p=fopen("Puerta.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Puerta), 0);
    bool leyo = fread(this, sizeof (Puerta), 1, p);
    fclose(p);
    return leyo;
}
