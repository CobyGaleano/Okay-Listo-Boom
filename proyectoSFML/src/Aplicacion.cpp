#include "Aplicacion.h"

Aplicacion::Aplicacion(sf::Vector2u resolucion)
{
    ///inicializacion de ventana
    _window = new sf::RenderWindow (sf::VideoMode(resolucion.x,resolucion.y), "BomberMan by:CompumundoHiperMegaDev");
    MainMenu _menu(_window->getSize().x, _window->getSize().y);///inicializar menu
    _evento = new sf::Event; ///inicializar evento
    _window->setFramerateLimit(10);
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
                iniciar();
                gameLoop();

            }
            break;
            case 2:{///cargar partida
                ///cargarPartida();
                cout << "OPCION CARGAR PARTIDA" << endl;
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


void Aplicacion::iniciar(){///aca se inicializan las variables y elementos que se utilizan dentro de la clase
    srand(time(0));

    _window->setFramerateLimit(60); ///setea fps
    ///PERSONAJE
    _pj = new Personaje(*_window);///inicializa personaje principal
    _vidasPJ=new Vida(*_window);
    _vidasPJ->setVidas(_pj->getCantVidas());
    _bomba=new Bomba(); ///inicializa la bomba
    _bombaActiva=false; ///estado de bomba en el mapa
    _explosion=new Explosion();///inicializa explosion
    ///MAPA
    _mapa = new Mapa(*_window);
    _cantBloques = _mapa->getCantBloques();
    _bloque=new Bloques;
    ///ENEMIGOS
    _cantE=5+rand()%5;///random entre 5 y 10 creo
    cout << _cantE << endl;
    _vEnemigos = new Enemigo[_cantE];///cantidad de enemigos
    posAnteriorEnemigo = new sf::Vector2f[_cantE]; ///vector para posiciones de enemigos
    for(int i=0;i<_cantE;i++)
    {
        sf::Vector2f posE(_mapa->posicionarEnemigos(i));
        _vEnemigos[i].respawn(posE);///ubica al enemigo en el mapa
    }

}

void Aplicacion::gameLoop(){
    while(!gameOver){ ///Mientras gameover sea falso, ejecuta el juego
        while (_window->pollEvent(*_evento))
        {
            if (_evento->type == sf::Event::Closed){
                _window->close();
                ///guardar partida
                gameOver=true;
            }
        }
            ///CMD CONTROLES
            procesar_eventos();
            ///UPDATES LOGICA DEL JUEGO
            procesar_logic();

            ///DRAWS - RENDERS
            renderizar();

    }
}
void Aplicacion::procesar_eventos (){
    ///aca habria que procesar todos los eventos por ejemplo los del teclado
    ///----CMD-----
    posAnteriorPJ=_pj->getPos();
    _pj->cmd();


}

void Aplicacion::procesar_logic (){
    ///creo que aca habria que revisar las coliciones e interactuar lo que pasa con el juego para despues mostrarlo
    ///----UPDATES-----
    sf::Vector2f pos;
    ///UPDATE MAPA -> chequea si se destruyo algun bloque
    _mapa->update();
    ///UPDATE DE PJ + CHECKEAR SUS COLISIONES
    _pj->update();
    _vidasPJ->setVidas(_pj->getCantVidas());
    ///comentado aca abajo .l.
    chequearColisionPJ();
    ///UPDATE DE ENEMIGOS
    for(int i=0;i<_cantE;i++)
    {
        posAnteriorEnemigo[i]=_vEnemigos[i].getPos();
        _vEnemigos[i].update();
        chequearColisionEnemigo();
    }
    ///PJ PONE BOMBA -> Por ahora solo puede poner una por vez y recien cuando explota
     if(_pj->getPusoBomba()==true && _bomba->getEstado()==false)
    {
        _pj->RestarBombas();
        pos=(_pj->getPos());
        _bomba->setEstado(_pj->getPusoBomba());
        _bomba->setPos(pos);
        std::cout<<_pj->getPos().x<<" "<<_pj->getPos().y<<endl;
        _pj->setPusoBomba(false);

    }
    _bomba->update();
    _explosion->setExplosion(_bomba->getExplosion());
    if(_explosion->getExplosion()==true)
    {
        _explosion->setPos(_bomba->getPos());
        _pj->SumarBomba();
        _explosion->update();
        _bomba->setExplosion(_explosion->getExplosion());

    }
    chequearColisionExplosion();
    //std::cout<<std::endl<<_bomba->getPos().x<<" "<<_bomba->getPos().y;
}

void Aplicacion::chequearColisionPJ(){
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        if(_pj->siColisiona(*_bloque)&&_bloque->getEstado()==true){
            cout << "choca" << endl;
            _pj->setPos(posAnteriorPJ);
            break;
        }
    }
    for(int i=0;i<_cantE;i++){
        if(_pj->siColisiona(_vEnemigos[i])){
            _pj->muere();
        }
    }
    if(_pj->siColisiona(*_explosion)){
        _pj->muere();
        cout << "ESTA ACA?" << endl;
        _bombaActiva=false;
    }
}

void Aplicacion::chequearColisionExplosion(){
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        if(_explosion->siColisiona(*_bloque)&& _bloque->getTipo()==2){
            _bloque->destruir();
            break;
        }
    }
}

void Aplicacion::chequearColisionEnemigo(){
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        for(int j=0; j<_cantE;j++){
            if(_vEnemigos[j].siColisiona(*_bloque)){
                _vEnemigos[j].setPos(posAnteriorEnemigo[j]);
            }
        }
    }
}

void Aplicacion::renderizar(){///en esta funcion va todos los draw
    _window->clear();
    ///----DRAW-----
    _window->draw(*_mapa);
    if(_bomba->getEstado()==true)
    {
        _window->draw(*_bomba);
    }
    if(_explosion->getExplosion()==true)
    {
        _window->draw(*_explosion);
    }
    _window->draw(*_vidasPJ);
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
    delete _vidasPJ;
    delete[] _vEnemigos;
    delete _mapa;
    delete _bomba;
    delete _explosion;
    delete _bloque;
    delete[] posAnteriorEnemigo;
}
