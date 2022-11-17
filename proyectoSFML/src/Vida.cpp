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
    _texto.setCharacterSize(20);
    _texto.setPosition(550,30);

    ///sprite corazon
    if(!_text.loadFromFile("corazon.png")){
        cout << "error"<< endl;
    }
    _sprite.setTexture(_text);
    _sprite.setTextureRect({2,2,23,23});
    _sprite.setPosition({_texto.getGlobalBounds().left+15,30});
}

void Vida::setVidas(int c){
    ///declarar un obj stream de la clase stringstream
    stringstream stream;
    stream<<c;
    ///cargar el stream en el string
    stream>>_cantidad;
    _texto.setString(_cantidad);

}

void Vida::draw(sf::RenderTarget& target,sf::RenderStates states)const //enseña a window como dibujar
{                                                                           //un personaje
    target.draw(_sprite,states);
    _ventana->draw(_texto);
}

bool Vida::guardarVida(){
    FILE *p;
    p=fopen("Enemigo.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Vida), 1, p);
    fclose(p);
    return escribio;
}
bool Vida::cargarVida(int pos){
    FILE *p;
    p=fopen("Vida.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Vida), 0);
    bool leyo = fread(this, sizeof (Vida), 1, p);
    fclose(p);
    return leyo;
}
