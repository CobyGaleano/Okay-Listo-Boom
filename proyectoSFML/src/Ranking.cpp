#include "Ranking.h"

Ranking::Ranking(){
}

Ranking::Ranking(sf::Vector2u resolucion)
{
    _estado=true;
    ///carga de la fuente
    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "Error al leer la fuente"<< endl;
    }
    ///carga del logo de la pantalla
    if(!_logoTexture.loadFromFile("Ranking.png")){
        cout << "Error al leer textura" << endl;
    }

    _titulo.setFont(_font);
    _titulo.setFillColor(sf::Color::Yellow);
    _titulo.setCharacterSize(30);
    _titulo.setString("RANKING");
    _titulo.setPosition(sf::Vector2f(resolucion.x/4,_titulo.getGlobalBounds().height+20));

    _logo.setTexture(_logoTexture);
    _logo.setOrigin(_logo.getGlobalBounds().width/2,0);///ARRIBA_CENTRO
    _logo.setScale(0.4f,0.4f);
    _logo.setPosition(sf::Vector2f((resolucion.x/2+_titulo.getGlobalBounds().width/3),0));

}

void Ranking::update(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        _estado=false;
    }
}

bool Ranking::getEstado(){
    return _estado;
}

Ranking::~Ranking()
{
}
void Ranking::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
    target.draw(_logo,states);
    target.draw(_titulo,states);
}
