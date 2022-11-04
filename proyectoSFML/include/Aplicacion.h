#ifndef APLICACION_H
#define APLICACION_H
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "GamePlay.h"
class Aplicacion
{
    private:
        sf::RenderWindow _window;
        MainMenu _menu;
        GamePlay _gamePlay;
    public:
        Aplicacion();

        void Run();

        ~Aplicacion();

    protected:

};

#endif // APLICACION_H
