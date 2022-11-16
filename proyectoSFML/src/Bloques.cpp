#include "Bloques.h"
Bloques::Bloques(){
    if(!_text.loadFromFile("bloques.png")){
        cout << "No se pudo cargar bloques" << endl;
    }
    _text.setRepeated(false);
    _sprite.setTexture(_text);
}
void Bloques::armar(int t, sf::Vector2f pos)
{
    _pos=pos;
    _tipo=t;
    int a;

    if(_tipo==1){
        a=0;
        _estado=true;
    }
    else if(_tipo==2){
        a=35;
        _estado=true;
    }

    _sprite.setTextureRect({a,0,35,30});
    _sprite.setPosition(sf::Vector2f(_pos.x*35,_pos.y*30));
}

void Bloques::destruir(){
    if(_tipo==2){
        _estado=false;
    }
}

bool Bloques::getEstado(){
    return _estado;
}

sf::Vector2f Bloques::getPos(){
    return _pos;
}


void Bloques::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al bloque
{
    target.draw(_sprite,states);
}

int Bloques::getTipo(){
    return _tipo;
}
sf::FloatRect Bloques::getBounds() const
{
    return _sprite.getGlobalBounds();
}
