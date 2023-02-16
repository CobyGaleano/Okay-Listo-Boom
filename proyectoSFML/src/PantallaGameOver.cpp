#include "PantallaGameOver.h"

PantallaGameOver::PantallaGameOver(float ancho, float alto,string puntos, string nJugador){
    Armar(40,"","GAME OVER",120,CENTRO, ancho,alto);
    _puntuacion = (puntos+" Puntos");
    _jugador = nJugador;

    ///carga de la fuente
    if(!_fontNombre.loadFromFile("FUENTE_NOMBRE.TTF"))
    {
        cout << "Error al leer la fuente"<< endl;
    }
    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "Error al leer la fuente"<< endl;
    }
    _titulo.setOrigin(_titulo.getGlobalBounds().width/2,_titulo.getGlobalBounds().height/2);
    _titulo.setPosition(ancho/2,alto/2);

    _tJugador.setString(_jugador);
    _tJugador.setFont(_fontNombre);
    _tJugador.setOrigin(_tJugador.getGlobalBounds().width/2,_tJugador.getGlobalBounds().height/2);
    _tJugador.setPosition(_titulo.getPosition().x,_titulo.getPosition().y+100);

    _tPuntuacion.setString(_puntuacion);
    _tPuntuacion.setFont(_fontPuntos);
    _tPuntuacion.setOrigin(_titulo.getGlobalBounds().width/2,_titulo.getGlobalBounds().height/2);
    _tPuntuacion.setPosition(_tJugador.getGlobalBounds().width,_tJugador.getPosition().y);
}
PantallaGameOver::~PantallaGameOver()
{
    //dtor
}
void PantallaGameOver::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_tJugador,states);
    target.draw(_tPuntuacion,states);

    PantallaTemporal::draw(target,states);

}
