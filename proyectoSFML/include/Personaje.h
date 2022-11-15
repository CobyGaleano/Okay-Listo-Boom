using namespace std;

#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "../Librerias.h"

enum class PersonajeState
{
    Idle=0,
    m_up,
    m_left,
    m_right,
    m_down,

};

class Personaje: public sf::Drawable, public Colisionable
{
    public:
        Personaje();
        void cmd();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void setPusoBomba(bool estado){_pusoBomba=estado;}
        sf::FloatRect getBounds() const override;
        void muere();
        bool getPusoBomba(){return _pusoBomba;}
        sf::Vector2f getPos(){return _sprite.getPosition();}


    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _velocity;

        sf::Vector2f _movePosition={0,0};

        float _frame;
        unsigned int _cantBombas;
        bool _pusoBomba;
        PersonajeState _state=PersonajeState::Idle;
};

#endif // PERSONAJE_H
