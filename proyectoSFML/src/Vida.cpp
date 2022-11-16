#include "Vida.h"

Vida::Vida(){
}

Vida::Vida(sf::RenderWindow &ventana)
{
    _ventana=&ventana;
    ///fuente para los numeros
    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "error"<< endl;
    }
    _texto.setFont(_font);
    _texto.setFillColor(sf::Color::White);
    _texto.setString("S/C");
    _texto.setCharacterSize(10);
    _texto.setPosition(_ventana->getSize().x-500,_ventana->getSize().y-250);

    ///sprite corazon
    if(!_text.loadFromFile("corazon.png")){
        cout << "error"<< endl;
    }
    _sprite.setTexture(_text);
    _sprite.setTextureRect({2,2,23,23});
    _sprite.setPosition({(float)_ventana->getSize().x-480,(float)_ventana->getSize().y-250});
}

void Vida::setVidas(int c){
    ///declarar un obj stream de la clase stringstream
    stringstream stream;
    stream<<c;
    ///cargar el stream en el string
    stream>>_cantidad;
    cout << c << endl; ///int
    cout <<_cantidad<<endl;///string

    _texto.setString(_cantidad);

}

void Vida::draw(sf::RenderTarget& target,sf::RenderStates states)const //enseña a window como dibujar
{                                                                           //un personaje
    target.draw(_sprite,states);
    _ventana->draw(_texto);
}
