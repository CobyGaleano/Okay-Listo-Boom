#ifndef BOMBA_H
#define BOMBA_H
#include <SFML/Graphics.hpp>
#include "../Librerias.h"

class Bomba: public sf::Drawable, public Colisionable
{
    public:
        Bomba();
        sf::Vector2f getPos(){return _sprite.getPosition();}
        sf::FloatRect getBounds() const override;

        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
        void respawn();
        void setPos(sf::Vector2f pos){
            _posicion=pos;
            sonido();
        }
        void setEstado(bool estado){_estado=estado;}
        void setExplosion(bool explosion){_explosion=explosion;}

        bool getEstado(){return _estado;}
        bool getExplosion(){return _explosion;}

        bool guardarBomba();
        bool cargarBomba(int pos);

        void sonido();
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _posicion;

        sf::SoundBuffer buffer;
        sf::Sound sound;

        bool _estado;
        float _frame;
        int _tiempo;
        bool _explosion;


};

#endif // BOMBA_H
