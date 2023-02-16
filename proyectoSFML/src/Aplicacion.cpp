#include "Aplicacion.h"

Aplicacion::Aplicacion(sf::Vector2u resolucion)
{
    ///inicializacion de ventana
    _window = new sf::RenderWindow (sf::VideoMode(resolucion.x,resolucion.y), "BomberMan by:CompumundoHiperMegaDev");
    MainMenu _menu(_window->getSize().x, _window->getSize().y);///inicializar menu
    _evento = new sf::Event; ///inicializar evento
    _window->setFramerateLimit(20);
    _resolucion=resolucion;
    int opcion;


    while(_window->isOpen()){
        while (_window->pollEvent(*_evento))
        {

            if (_evento->type == sf::Event::Closed){
                _window->close();
                ///guardar partida
            }
        }
        _menu.cmd();

        if(_menu.getState()){

            opcion=_menu.getSelected();
            switch(opcion){
            case 1:{///play
                cout << "OPCION PLAY" << endl;
                cout << "Cargando juego" << endl;
                _nombre=cargarNombre();
                int nivel=1;
                bool salirAlMenu=false;
                while(!salirAlMenu){
                    switch(nivel){
                        case 1:{
                            _window->clear();
                            gamePlay=new Gameplay(resolucion,*_window,nivel,_nombre);
                            if(gamePlay->getGameOver()){
                                salirAlMenu=true;
                            }
                            if(gamePlay->getLevelUp()==true){
                                nivel++;
                            }
                        };
                        break;
                        case 2:{

                            gamePlay=new Gameplay(resolucion,*_window,nivel,_nombre);
                            if(gamePlay->getLevelUp()==true){
                                nivel++;
                            }
                        }
                        break;
                        case 3:{
                            gamePlay=new Gameplay(resolucion,*_window,nivel,_nombre);
                            if(gamePlay->getLevelUp()==true){
                                nivel++;
                            }
                        }
                    }
                }

            }
            break;
            case 2:{///cargar partida
                ///cargarPartida();
                cout << "OPCION CARGAR PARTIDA" << endl;
                gamePlay=new Gameplay;
                bool cargo=gamePlay->cargarPartida(1);
                if(!cargo){
                    cout << "Error al cargar partida" << endl;
                }else{
                    cout << "Partida cargada con exito" << endl;
                }
                gamePlay->setGameOver(false);
                gamePlay->run(resolucion,*_window);
            }
            break;
            case 3:{///ranking
                ///ranking();
                cout << "OPCION RANKING" << endl;
                _ranking = new Ranking(_resolucion);
                while(_ranking->getEstado()==true){
                    _window->clear();
                    _ranking->update();
                    _window->draw(*_ranking);
                    _window->display();
                }
                delete _ranking;
            }
            break;
            case 4:{///exit
                _window->close();
                cout << "OPCION EXIT" << endl;
            }
            break;
            }
        }
        _menu.update();
        _window->clear();
        _menu.draw(*_window);
        _window->display();
    }

}

string Aplicacion::cargarNombre(){
    sf::Text _text;
    sf::Text _titulo;
    sf::Font _font;
    string nombre;
    bool _estado=false;

    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "Error al leer la fuente"<< endl;
    }
    _titulo.setFont(_font);
    _titulo.setFillColor(sf::Color::Yellow);
    _titulo.setCharacterSize(30);
    _titulo.setString("Ingresa tu nombre:  ");
    //_titulo.setOrigin(_titulo.getGlobalBounds().width,_titulo.getGlobalBounds().height);
    _titulo.setPosition(0,0);
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Yellow);
    _text.setCharacterSize(30);
    _text.setPosition(_titulo.getGlobalBounds().width,_titulo.getPosition().y);



    while (!_estado)
    {
        // Handle events
        sf::Event event;
        while (_window->pollEvent(event))
        {

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8 && _text.getString().getSize() > 0)
                {
                    // Backspace
                    nombre = _text.getString();
                    nombre.pop_back();
                    _text.setString(nombre);
                }
                else if (event.text.unicode == 13)
                {
                    // Enter
                     nombre = _text.getString();
                    // Do something with the nickname
                    _estado=true;
                }
                else if (event.text.unicode < 128)
                {
                    // Add a character
                     nombre = _text.getString();
                    nombre += static_cast<char>(event.text.unicode);
                    _text.setString(nombre);
                }
            }
        }

        // Clear the window
        _window->clear();

        // Draw the text
        _window->draw(_titulo);
        _window->draw(_text);

        // Display the window
        _window->display();
    }

    _nombre= nombre;
    return _nombre;
}


Aplicacion::~Aplicacion(){
    delete gamePlay;
    delete _evento;
    delete _window;
}
