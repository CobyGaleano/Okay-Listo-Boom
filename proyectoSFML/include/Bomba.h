#ifndef BOMBA_H
#define BOMBA_H
#include "../Librerias.h"

class Bomba: public sf::Drawable, public Colisionable
{
    public:
        Bomba();
        sf::Vector2f getPos(){return _sprite.getPosition();}
        sf::FloatRect getBounds() const override;

        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void respawn();
        void setPos(sf::Vector2f pos){_posicion=pos;}
        void setEstado(bool estado){_estado=estado;}
        void setExplosion(bool explosion){_explosion=explosion;}

        bool getEstado(){return _estado;}
        bool getExplosion(){return _explosion;}


    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _posicion;
        bool _estado;
        float _frame;
        float _tiempo;
        bool _explosion;


};

#endif // BOMBA_H
