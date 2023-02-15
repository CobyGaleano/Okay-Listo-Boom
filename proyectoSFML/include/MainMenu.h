#ifndef MAINMENU_H
#define MAINMENU_H
#define CANT_ITEMS 4
#include <iostream>
using namespace std;
#include "../Librerias.h"
#include <SFML/Audio.hpp>


enum ESTADO{
    ARRIBA,
    ABAJO,
    SELECT,
    WAITING
};

class MainMenu
{
    private:
        sf::Font _font;
        sf::Text _menu[CANT_ITEMS];
        sf::Sprite _sprite;
        sf::Texture _text;

        sf::SoundBuffer buffer;
        sf::Sound sound;

        int _selected;
        ESTADO _state;
        int _tiempo;

    public:
        MainMenu();
        MainMenu(float ancho,float alto);

        void cmd();
        void update();
        void draw(sf::RenderWindow& window);

        int getSelected();
        bool getState();

        ~MainMenu();
};

#endif // MAINMENU_H
