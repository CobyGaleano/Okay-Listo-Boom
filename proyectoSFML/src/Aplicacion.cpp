#include "Aplicacion.h"

Aplicacion::Aplicacion(sf::Vector2u resolucion)
{
    ///inicializacion de ventana
    _window = new sf::RenderWindow (sf::VideoMode(resolucion.x,resolucion.y), "BomberMan by:CompumundoHiperMegaDev");
    MainMenu _menu(_window->getSize().x, _window->getSize().y);///inicializar menu
    _evento = new sf::Event; ///inicializar evento
    _window->setFramerateLimit(20);
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
                int nivel=1;
                switch(nivel){
                    case 1:{
                        pantallaDelNivel= new PantallaNivel(600,450,1);
                        while(pantallaDelNivel->getEstado()==true){
                            pantallaDelNivel->update();
                            _window->clear();
                            _window->draw(*pantallaDelNivel);
                            _window->display();
                        }
                        delete pantallaDelNivel;
                        gamePlay=new Gameplay(resolucion,*_window);
                        if(gamePlay->getLevelUp()==true){
                            nivel++;
                        }
                    };
                    break;
                    case 2:{
                        gamePlay=new Gameplay(resolucion,*_window);
                        if(gamePlay->getLevelUp()==true){
                            nivel++;
                        }
                    }
                    break;
                    case 3:{
                        gamePlay=new Gameplay(resolucion,*_window);
                        if(gamePlay->getLevelUp()==true){
                            nivel++;
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

Aplicacion::~Aplicacion(){
    delete gamePlay;
    delete pantallaDelNivel;
    delete _evento;
    delete _window;
}
