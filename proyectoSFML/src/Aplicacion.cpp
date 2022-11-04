#include "Aplicacion.h"

Aplicacion::Aplicacion()
{
    ///inicializacion de ventana
    sf::RenderWindow window(sf::VideoMode(525,450), "CompuMundoHiperMegaDev");
    window.setFramerateLimit(75);

    MainMenu m(window.getSize().x, window.getSize().y);
    _menu = m;
}


void Aplicacion::Run(){
    while (_window.isOpen())
    {

        // Read InPut: Atualizar los estados de los perifericos de entrada
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }


        //CMD - Joy



        //Update - Actualiza los estados del juego



        //limpia la pantalla
        _window.clear();

        //Draw - Dibuja en la pantalla

        //Display - Flip
        _window.display();

    }

    //Liberacion del juego
}

Aplicacion::~Aplicacion()
{
    //dtor
}
