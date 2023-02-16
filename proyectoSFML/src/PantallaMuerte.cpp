#include "PantallaMuerte.h"

PantallaMuerte::PantallaMuerte(float ancho, float alto){
    Armar(40,"","Moriste",60,CENTRO, ancho,alto);

}

PantallaMuerte::~PantallaMuerte()
{
    //dtor
}
void PantallaMuerte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    PantallaTemporal::draw(target,states);
}
