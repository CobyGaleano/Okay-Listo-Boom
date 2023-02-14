#ifndef PANTALLANIVEL_H
#define PANTALLANIVEL_H

#include "../Librerias.h"
#include "PantallaTemporal.h"


class PantallaNivel: public PantallaTemporal
{
    public:
        PantallaNivel(float ancho, float alto, int nivel);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ~PantallaNivel();
    private:
};

#endif // PANTALLANIVEL_H
