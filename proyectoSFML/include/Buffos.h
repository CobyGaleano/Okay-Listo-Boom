#ifndef BUFFOS_H
#define BUFFOS_H
#include <../Librerias.h>

class Buffos: public sf::Drawable, public Colisionable
{
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _posicion;

        sf::SoundBuffer bufferDaleBoca;
        sf::Sound soundDaleBoca;

        bool _estado;
        bool _TocoBuffo;
    public:
        Buffos();
        sf::FloatRect getBounds() const override;

        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
        void update();
        void respawn();
        void setPos(sf::Vector2f pos){_posicion=pos;}
        void setEstado(bool estado){_estado=estado;}
        void setTocoBuffo(bool toco){_TocoBuffo=toco;}

        bool getEstado(){return _estado;}
        bool getTocoBuffo(){return _TocoBuffo;}
        Buffos& getBuffo();

        bool guardarBuffos();
        bool cargarBuffos(int pos);
};

#endif // BUFFOS_H
