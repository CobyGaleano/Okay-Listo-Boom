#ifndef PANTALLATEMPORAL_H
#define PANTALLATEMPORAL_H

#include "../Librerias.h"

enum POSICION{

    ARRIBA_CENTRO,
    ARRIBA_IZQUIERDA,
    ABAJO_CENTRO,
    CENTRO

};

class PantallaTemporal: public sf::Drawable
{
    protected:
        sf::Font _font;
        int _fontSize;
        sf::Text _titulo;

        int _duracion;
        int _tiempo;
        float _anchoP;
        float _altoP;

        string _archivoLogo;
        sf::Sprite _logo;
        sf::Texture _logoTexture;
        POSICION _posicionLogo;

        bool _estado;
    public:
        PantallaTemporal();
        ~PantallaTemporal();
        void Armar(int fSize,string nombreArch,string titulo,int duracion,POSICION pos, float ancho, float alto);

        bool getEstado();

        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
};

#endif // PANTALLATEMPORAL_H
