#ifndef PANTALLAGAMEOVER_H
#define PANTALLAGAMEOVER_H

#include "../Librerias.h"
#include "PantallaTemporal.h"

class PantallaGameOver: public PantallaTemporal
{
    public:
        PantallaGameOver(float ancho, float alto);
        ~PantallaGameOver();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:

    private:
};

#endif // PANTALLAGAMEOVER_H
