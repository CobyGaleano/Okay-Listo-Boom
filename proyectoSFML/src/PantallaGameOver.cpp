#include "PantallaGameOver.h"

PantallaGameOver::PantallaGameOver(float ancho, float alto){
    Armar(40,"","GAME OVER",60,CENTRO, ancho,alto);
}
PantallaGameOver::~PantallaGameOver()
{
    //dtor
}
void PantallaMuerte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    PantallaTemporal::draw(target,states);
}
