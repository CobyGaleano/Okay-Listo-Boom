using namespace std;

#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Vida.h"
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
        Personaje(sf::RenderWindow &ventana);
        ~Personaje();
        void cmd();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void setPos(sf::Vector2f pos);

        void setPusoBomba(bool estado){_pusoBomba=estado;}
        void RestarBombas(){_cantBombas--;}
        void SumarBomba(){_cantBombas++;}
        unsigned int getCantBombas(){return _cantBombas;}
        bool getPusoBomba(){return _pusoBomba;}

        void muere();
        sf::FloatRect getBounds() const override;
        sf::Vector2f getPos(){return _sprite.getPosition();}

        int getCantVidas(){return _cantVidas;}
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _velocity;
        sf::SoundBuffer buffer;
        sf::Sound sound;

        sf::Vector2f _movePosition={0,0};

        float _frame;
        unsigned int _cantBombas;
        bool _pusoBomba;
        PersonajeState _state=PersonajeState::Idle;

        int _cantVidas;
        sf::RenderWindow * _ventana;
};

#endif // PERSONAJE_H
