#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Personaje.h"
#include "Colisionable.h"

class Enemigo: public sf::Drawable, public Colisionable
{
    public:
        Enemigo();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void respawn();
        void damage();
        sf::FloatRect getBounds() const override;

    private:
        sf::Sprite _sprite;
        sf::Texture _text;
        sf::Vector2f _velocity;
        sf::Vector2f _newPosition;
        int _timeRespawn;
        float _frame;

};

#endif // ENEMIGO_H
