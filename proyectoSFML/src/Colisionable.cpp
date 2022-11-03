#include "Colisionable.h"

Colisionable::Colisionable()
{
    //ctor
}

bool Colisionable::siColisiona(Colisionable &obj)const
{
    return getBounds().intersects(obj.getBounds());
}
