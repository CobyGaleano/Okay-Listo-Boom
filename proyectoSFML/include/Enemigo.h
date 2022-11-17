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
        void respawn(sf::Vector2f pos);
        void damage();

        sf::Vector2f getPos(){return _sprite.getPosition();}
        sf::FloatRect getBounds() const override;

        void setPos(sf::Vector2f p);
        void setEstado(bool es){_estado=es;}
        bool getEstado(){return _estado;}

        bool guardarEnemigo(int pos);
        bool cargarEnemigo(int pos);

    private:
        sf::Sprite _sprite;
        sf::Texture _text;
        sf::Vector2f _velocity;
        sf::Vector2f _newPosition;
        int _timeRespawn;
        int _moovSelect;
        float _timeMoov;
        float _frame;
        bool _estado;

};

#endif // ENEMIGO_H
