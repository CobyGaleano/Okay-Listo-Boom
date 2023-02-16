#ifndef PANTALLAMUERTE_H
#define PANTALLAMUERTE_H

#include "../Librerias.h"
#include "PantallaTemporal.h"

class PantallaMuerte: public PantallaTemporal
{
    public:
        PantallaMuerte(float ancho, float alto);
        ~PantallaMuerte();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



    private:

};

#endif // PANTALLAMUERTE_H
