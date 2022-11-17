#include "Gameplay.h"

Gameplay::Gameplay(){
}

Gameplay::Gameplay(sf::Vector2u resolucion, sf::RenderWindow &window){
    _window = &window;
    iniciar();
    gameLoop();
}
void Gameplay::run(sf::Vector2u resolucion, sf::RenderWindow &window){
    _window = &window;
    _evento=new sf::Event;
    cout << "ESTA EN RUN" <<endl;
    iniciar();
    cargarJuego();
    gameLoop();
}

void Gameplay::iniciar(){///aca se inicializan las variables y elementos que se utilizan dentro de la clase
    srand(time(0));

    _window->setFramerateLimit(60); ///setea fps
    _evento = new sf::Event; ///inicializar evento
    ///PERSONAJE
    _pj = new Personaje(*_window);///inicializa personaje principal
    _vidasPJ=new Vida(*_window);
    _vidasPJ->setVidas(_pj->getCantVidas());
    _puntajePJ=new Puntaje(*_window);
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

void Gameplay::gameLoop(){
    while(!gameOver){ ///Mientras gameover sea falso, ejecuta el juego
        while (_window->pollEvent(*_evento))
        {
            if (_evento->type == sf::Event::Closed){
                bool guardo=guardarPartida();
                if(!guardo){
                    cout << "Error al guardar partida"<<endl;
                }else{
                    cout << "Partida guardada con exito"<<endl;
                }
                _window->close();
                gameOver=true;
            }
        }
            ///CMD CONTROLES
            cout << "Iniciando gameLoop" << endl;
            procesar_eventos();
            ///UPDATES LOGICA DEL JUEGO
            procesar_logic();

            ///DRAWS - RENDERS
            renderizar();

    }
}
void Gameplay::procesar_eventos (){
    ///aca habria que procesar todos los eventos por ejemplo los del teclado
    ///----CMD-----
    cout << "Entra en procesar eventos" << endl;
    posAnteriorPJ=_pj->getPos();
    _pj->cmd();
    cout << "Procesa eventos correctamente"<<endl;

}

void Gameplay::procesar_logic (){
    cout << "Procesando logica" << endl;
    ///creo que aca habria que revisar las coliciones e interactuar lo que pasa con el juego para despues mostrarlo
    ///----UPDATES-----
    sf::Vector2f pos;
    ///UPDATE MAPA -> chequea si se destruyo algun bloque
    _mapa->update();
    ///UPDATE DE PJ + CHECKEAR SUS COLISIONES
    _pj->update();
    _vidasPJ->setVidas(_pj->getCantVidas());
    if(_pj->getCantVidas()<=0){
        gameOver=true;
    }
    _puntajePJ->setPuntaje(_pj->getPuntaje());
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
        _explosion->setPos(pos);
        _pj->SumarBomba();
        _explosion->update();
        _bomba->setExplosion(_explosion->getExplosion());

    }
    chequearColisionExplosion();
    //std::cout<<std::endl<<_bomba->getPos().x<<" "<<_bomba->getPos().y;
    cout << "Procesa logica correctamente" <<endl;
}

void Gameplay::chequearColisionPJ(){
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        if(_pj->siColisiona(*_bloque)&&_bloque->getEstado()==true){
            cout << "choca" << endl;
            _pj->setPos(posAnteriorPJ);
            break;
        }
    }
    for(int i=0;i<_cantE;i++){
        if(_pj->siColisiona(_vEnemigos[i])&&_vEnemigos[i].getEstado()==true){
            _pj->muere();
        }
    }
    /*if(_pj->siColisiona(*_explosion)){
        _pj->muere();
        cout << "ESTA ACA?" << endl;
        _bombaActiva=false;
    }*/
}

void Gameplay::chequearColisionExplosion(){
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        if(_explosion->siColisiona(*_bloque)&& _bloque->getTipo()==2){
            _bloque->destruir();
            break;
        }
    }
    for(int i=0;i<_cantE;i++){
        for(int j=0; j<_cantE;j++){
            if(_explosion->siColisiona(_vEnemigos[i])&&_vEnemigos[i].getEstado()==true){
                _vEnemigos[j].setPos(posAnteriorEnemigo[j]);
                _vEnemigos[j].setEstado(false);///si la explosion toca al enemigo, lo da de baja
                _pj->setPuntaje(_pj->getPuntaje()+10);
            }
        }
    }
}

void Gameplay::chequearColisionEnemigo(){
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        for(int j=0; j<_cantE;j++){
            if(_vEnemigos[j].siColisiona(*_bloque)){
                _vEnemigos[j].setPos(posAnteriorEnemigo[j]);
            }
        }
    }

}

void Gameplay::renderizar(){///en esta funcion va todos los draw
    _window->clear();
    cout << "RENDER" << endl;
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
    _window->draw(*_puntajePJ);
    _window->draw(*_pj);
    cout << "Renderiza correctamente" << endl;
    for(int i=0;i<_cantE;i++)
    {
        if(_vEnemigos[i].getEstado()==true){
            _window->draw(_vEnemigos[i]);
        }
    }
    ///------------
    _window->display();
}

int Gameplay::getCantEnemigos(){
    return _cantE;  ///devuelve la cantidad de enemigos (creo que puede ser util mas adelante)
}

bool Gameplay::guardarPartida(){
    FILE *p;
    p=fopen("Partidas.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Gameplay), 1, p);
    fclose(p);
    _pj->guardarPersonaje();
    _bomba->guardarBomba();
    _vidasPJ->guardarVida();
    _puntajePJ->guardarPuntaje();
    _mapa->guardarMapa();
    for(int i=0;i<_cantE;i++){
        _vEnemigos[i].guardarEnemigo(i);
    }
    return escribio;
}
bool Gameplay::cargarPartida(int pos){
    FILE *p;
    p=fopen("Partidas.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Gameplay), 0);
    bool leyo = fread(this, sizeof (Gameplay), 1, p);
    fclose(p);
    return leyo;
}
bool Gameplay::cargarJuego(){
    ///va a cargar todos los archivos, iniciar los objetos y cargarlos desde el disco.
    _pj->cargarPersonaje(1);
    _bomba->cargarBomba(1);
    _vidasPJ->cargarVida(1);
    _puntajePJ->cargarPuntaje(1);
    _mapa->cargarMapa(1);
    _cantBloques = _mapa->getCantBloques();
    for(int i=0;i<_cantE;i++){
        _vEnemigos[i].cargarEnemigo(i);
        posAnteriorEnemigo[i]=_vEnemigos[i].getPos();
    }

}

Gameplay::~Gameplay(){
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
