#include "Aplicacion.h"

Aplicacion::Aplicacion(sf::Vector2u resolucion)
{
    ///inicializacion de ventana
    _window = new sf::RenderWindow (sf::VideoMode(resolucion.x,resolucion.y), "BomberMan by:CompumundoHiperMegaDev");
    iniciar();
    gameLoop();
}


void Aplicacion::iniciar(){///aca se inicializan las variables y elementos que se utilizan dentro de la clase
    srand(time(0));

    _window->setFramerateLimit(60); ///setea fps
    _evento = new sf::Event; ///inicializar evento
    MainMenu _menu(_window->getSize().x, _window->getSize().y);///inicializar menu
    _pj = new Personaje();///inicializa personaje principal
    _bomba=new Bomba(); ///inicializa la bomba
    _cantE=5+rand()%5;///random entre 5 y 10 creo
    cout << _cantE << endl;
    _vEnemigos = new Enemigo[_cantE];///cantidad de enemigos
    for(int i=0;i<_cantE;i++)
    {
    _vEnemigos[i].respawn();///ubica al enemigo en el mapa
    }
    _mapa = new Mapa;

}

void Aplicacion::gameLoop(){
    while(!gameOver){ ///Mientras gameover sea falso, ejecuta el juego
        while (_window->pollEvent(*_evento))
        {
            if (_evento->type == sf::Event::Closed){
                _window->close();
            }
            ///CMD CONTROLES
            procesar_eventos();
            ///UPDATES LOGICA DEL JUEGO
            procesar_logic();

            ///DRAWS - RENDERS
            renderizar();
        }
    }
}
void Aplicacion::procesar_eventos (){
    ///aca habria que procesar todos los eventos por ejemplo los del teclado
    ///----CMD-----
    _pj->cmd();

}
void Aplicacion::procesar_logic (){
    ///creo que aca habria que revisar las coliciones e interactuar lo que pasa con el juego para despues mostrarlo
    ///----UPDATES-----
    _pj->update();
    for(int i=0;i<_cantE;i++)
    {
    _vEnemigos[i].update();
    }
    _bomba->update();
}

void Aplicacion::renderizar(){///en esta funcion va todos los draw
    _window->clear();
    ///----DRAW-----
    _window->draw(*_mapa);
    _window->draw(*_bomba);
    _window->draw(*_pj);
     for(int i=0;i<_cantE;i++)
    {
    _window->draw(_vEnemigos[i]);
    }
    ///------------
    _window->display();
}

int Aplicacion::getCantEnemigos(){
    return _cantE;  ///devuelve la cantidad de enemigos (creo que puede ser util mas adelante)
}

Aplicacion::~Aplicacion(){
    delete _evento;
    delete _window;
    delete _pj;
    delete _vEnemigos;
    delete _mapa;
    delete _bomba;
}
