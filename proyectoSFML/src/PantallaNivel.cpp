#include "PantallaNivel.h"

PantallaNivel::PantallaNivel(float ancho, float alto, int nivel){


    switch(nivel){
    case 1:
        Armar(40,"Nivel_1","Nivel 1",600,CENTRO, ancho,alto);
        break;
    case 2:
        Armar(40,"Nivel 2","Nivel 2",600,CENTRO, ancho,alto);
        break;
    case 3:
        Armar(40,"Nivel 2","Nivel 2",600,CENTRO, ancho,alto);
        break;
    }
}
void PantallaNivel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    PantallaTemporal::draw(target,states);
}
