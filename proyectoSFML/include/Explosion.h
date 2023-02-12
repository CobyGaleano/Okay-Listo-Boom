#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "../Librerias.h"

class Explosion: public sf::Drawable, public Colisionable
{
    public:
        Explosion();
        ~Explosion();
        sf::FloatRect getBounds() const override;
        ///sf::Vector2f getPos(){return _sprite.getPosition();}

        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
        void update();
        void setExplosion(bool flag){_explosion=flag;}
        void setPos(sf::Vector2f pos){_posicion=pos;}

        bool getExplosion(){return _explosion;}

        void rotar(){_sprite.rotate(90);};

    private:
        sf::Sprite _sprite;///horizontal 0 - vertical 1

        sf::Texture _texture;
        sf::Vector2f _posicion;

        bool _explosion;

        float _frame;
        float _tiempo;


};

#endif // EXPLOSION_H
