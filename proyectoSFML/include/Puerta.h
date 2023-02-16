#ifndef PUERTA_H
#define PUERTA_H
#include <../Librerias.h>


class Puerta: public sf::Drawable, public Colisionable
{
    public:
        Puerta();
        sf::FloatRect getBounds() const override;

        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
        void update(int cantE);
        void respawn();
        void setPos(sf::Vector2f pos){_posicion=pos;}
        void setEstado(bool estado){_estado=estado;}

        bool getEstado(){return _estado;}
        Puerta& getPuerta();

        bool guardarPuerta();
        bool cargarPuerta(int pos);

    private:

        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _posicion;

        sf::SoundBuffer bufferDaleBoca;
        sf::Sound soundDaleBoca;

        bool _estado;
};

#endif // PUERTA_H
