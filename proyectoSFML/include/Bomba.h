#ifndef BOMBA_H
#define BOMBA_H
#include "../Librerias.h"

class Bomba: public sf::Drawable
{
    public:
        Bomba();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void respawn();
        void setPos(sf::Vector2f pos){_posicion=pos;}
        void setEstado(bool estado){_estado=estado;}
        sf::Vector2f getPos(){_sprite.getPosition();}


    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        float _frame;
        sf::Vector2f _posicion;
        bool _estado;

};

#endif // BOMBA_H
