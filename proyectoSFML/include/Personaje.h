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
        Personaje();
        ~Personaje();
        void cmd();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        void setPos(sf::Vector2f pos);

        void setPusoBomba(bool estado){_pusoBomba=estado;}
        void setCantBombas(int cant){_cantBombas=cant;}
        void RestarBombas(){_cantBombas--;}
        void SumarBomba(){_cantBombas++;}
        void setMuerto(bool muerto){_muerto=muerto;}
        void setRespawn(bool respawn){_respawn=respawn;}
        void setChupoFernet(bool fernet){_chupoFernet=fernet;}
        unsigned int getCantBombas(){return _cantBombas;}
        bool getPusoBomba(){return _pusoBomba;}
        bool getMuerto(){return _muerto;}
        bool getEstadoRespawn(){return _respawn;}
        bool getChupoFernet(){return _chupoFernet;}
        sf::Vector2f getPosBomba(){return _posBomba;}

        void muere();
        void respawn();
        sf::FloatRect getBounds() const override;
        sf::Vector2f getPos(){return _sprite.getPosition();}

        bool cargarPersonaje(int pos);
        bool guardarPersonaje();
        int getCantVidas(){return _cantVidas;}
        bool getSeMueve(){return _semueve;}
        int getPuntaje(){return _puntaje;}
        void setPuntaje(int p){_puntaje=p;}

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _velocity;
        sf::SoundBuffer buffer;
        sf::Sound sound;

        sf::SoundBuffer bufferMuerte;
        sf::Sound soundMuerte;

        sf::Vector2f _movePosition={0,0};
        sf::Vector2f _posBomba;
        float _frame;
        unsigned int _cantBombas;
        bool _pusoBomba;
        bool _semueve;
        int _contMov;
        bool _muerto;
        bool _respawn;
        PersonajeState _state=PersonajeState::Idle;

        bool _chupoFernet;

        int _cantVidas;
        int _puntaje;
        sf::RenderWindow * _ventana;
};

#endif // PERSONAJE_H
