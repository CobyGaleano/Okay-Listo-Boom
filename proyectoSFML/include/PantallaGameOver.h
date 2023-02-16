#ifndef PANTALLAGAMEOVER_H
#define PANTALLAGAMEOVER_H

#include "../Librerias.h"
#include "PantallaTemporal.h"

class PantallaGameOver: public PantallaTemporal
{
    public:
        PantallaGameOver(float ancho, float alto, string puntos, string nJugador);
        ~PantallaGameOver();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        string _puntuacion;
        string _jugador;

        sf::Text _tPuntuacion;
        sf::Text _tJugador;
        sf::Font _fontNombre;
        sf::Font _fontPuntos;
};

#endif // PANTALLAGAMEOVER_H
