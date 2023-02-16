#ifndef PANTALLACARGANOMBRE_H
#define PANTALLACARGANOMBRE_H

#include "../Librerias.h"
#include <SFML/Graphics.hpp>


class PantallaCargaNombre: public sf::Drawable
{
    public:
        PantallaCargaNombre(sf::RenderWindow &ventana);
        ~PantallaCargaNombre();
        void cargarNombre();

        string getNombre();
        bool getEstado();



    private:

        sf::Text _text;
        sf::Font _font;
        sf::RenderWindow * _ventana;

        bool _estado;

        std::string _nombre;

};

#endif // PANTALLACARGANOMBRE_H
