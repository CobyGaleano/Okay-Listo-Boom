#ifndef MAINMENU_H
#define MAINMENU_H
#define CANT_ITEMS 4
#include <iostream>
using namespace std;
#include "../Librerias.h"


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
        int _selected;
        ESTADO _state;

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
