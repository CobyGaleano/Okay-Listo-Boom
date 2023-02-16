#include "Gameplay.h"

Gameplay::Gameplay(){
}

Gameplay::Gameplay(sf::Vector2u resolucion, sf::RenderWindow &window,int nivel,string nombre){
    _window = &window;
    _resolucion = resolucion;
    _nivel=nivel;
    _nombre=nombre;
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

    armarNivel(_nivel);
}

void Gameplay::gameLoop(){
    while(!gameOver&&!_levelUp){ ///Mientras gameover sea falso, ejecuta el juego
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
            procesar_eventos();
            ///UPDATES LOGICA DEL JUEGO
            procesar_logic();

            ///DRAWS - RENDERS
            renderizar();

        if(gameOver){
            pGameOver=new PantallaGameOver(_resolucion.x,_resolucion.y,_puntajePJ->getPuntaje(),_nombre);
            while(pGameOver->getEstado()==true){
                pGameOver->update();
                _window->clear();
                _window->draw(*pGameOver);
                _window->display();
            }
            delete pGameOver;
        }
    }
}
void Gameplay::procesar_eventos (){///procesa los ingresos por teclado
    ///aca habria que procesar todos los eventos por ejemplo los del teclado
    ///----CMD-----
    posAnteriorPJ=_pj->getPos();
    _pj->cmd();

}

void Gameplay::procesar_logic (){///procesa la logica del juego
    ///creo que aca habria que revisar las coliciones e interactuar lo que pasa con el juego para despues mostrarlo
    ///----UPDATES-----
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
    if(_buffo->getEstado()){
        chequearColisionBuffo();
    }
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
        _bomba->setPos(_pj->getPosBomba());
        _bomba->setEstado(true);
    }

    _bomba->update();
    if(_bomba->getExplosion()==true){
        _explosion[0].setExplosion(true);
        _explosion[1].setExplosion(true);
        _bomba->setExplosion(false);
    }
    /*for(int i=0;i<2;i++){
        _explosion[i].setExplosion(_bomba->getExplosion());
    }*/

    if(_explosion[0].getExplosion()==true && _explosion[1].getExplosion()==true){
        _bomba->setEstado(false);

        for(int i=0;i<2;i++){
            _explosion[i].setPos(_bomba->getPos());
            _explosion[i].update();
        }
        chequearColisionExplosion();///chequear posicion fuera del for sino toma
                                    ///  la posicion de la bomba anterior
        _pj->SumarBomba();
        _pj->setPusoBomba(false);
    }
    _buffo->update();
    chequearColisionPuerta();
    _puerta->update(_cantE);
}

void Gameplay::chequearColisionPJ(){///chequea las colisiones del pj
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        if(_pj->siColisiona(*_bloque)&&_bloque->getEstado()==true){
            _pj->setPos(posAnteriorPJ);
            break;
        }
    }
    if(_pj->siColisiona(*_bomba)&&_pj->getSeMueve()&&_bomba->getEstado()){
        _pj->setPos(posAnteriorPJ);
    }
    /*for(int i=0;i<_cantE;i++){
        if(_pj->siColisiona(_vEnemigos[i])&&_vEnemigos[i].getEstado()==true){
            cout<<endl<<"PJ TOCA ENEMIGO";
           //_pj->muere();
           if(_pj->getCantVidas()<=0){
                gameOver=true;
            }
           if(!gameOver){
                resetLevel();
           }
           // _pj->setMuerto(true);//setea el booleano de pj para saber si muere
            }
    }*/
}

void Gameplay::chequearColisionExplosion(){///chequea las colisiones de las explosiones
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        for(int j=0;j<2;j++){
            if(_explosion[j].siColisiona(*_bloque)&& _bloque->getTipo()==2&&_bloque->getEstado()==true){
                _bloque->destruir();
                cout<< "destruido" << endl;
                //break;
            }
        }
    }
    //for(int i=0;i<_cantE;i++){
        for(int j=0; j<_cantE;j++){
            for(int i=0;i<2;i++){
                if(_explosion[i].siColisiona(_vEnemigos[j])&&_vEnemigos[j].getEstado()==true){
                    _vEnemigos[j].setEstado(false);///si la explosion toca al enemigo, lo da de baja
                    _pj->setPuntaje(_pj->getPuntaje()+10);
                    _enemigosActivos--;
                    if(_enemigosActivos<=0){
                        _levelUp=true;
                    }
                    if(_vEnemigos[j].getEstado()==false){
                        cout<<"toca enemigo"<<endl;
                    }
                }
            }
        }
    ///Chequea la colision entre el personaje y la explosion
    /*for(int i=0;i<2;i++){
        if(_explosion[i].siColisiona(*_pj)&&_explosion[i].getExplosion()==true){
            cout<<endl<<_pj->getMuerto();
            _pj->muere();
            if(_pj->getCantVidas()<=0){
                    gameOver=true;
            }
            if(!gameOver){
                    resetLevel();
            }
            //_pj->setMuerto(true);//setea el booleano de pj para saber si muere
            cout<<endl<<"PJ TOCA EXPLOSION"<<endl<<_pj->getMuerto();//chequeo de entrada

        }
    }*/

}

void Gameplay::chequearColisionEnemigo(){///chequea las colisiones de los enemigos
    for(int i=0;i<_cantBloques;i++){
        _bloque=_mapa->getBloque(i);
        for(int j=0; j<_cantE;j++){
            if(_vEnemigos[j].siColisiona(*_bloque)){
                _vEnemigos[j].setPos(posAnteriorEnemigo[j]);
            }
        }
    }
    for(int j=0; j<_cantE;j++){
        if(_vEnemigos[j].siColisiona(*_bomba)&&_bomba->getEstado()){
            _vEnemigos[j].setPos(posAnteriorEnemigo[j]);
        }
    }
}

void Gameplay::chequearColisionBuffo()///chequea la colision del buffo y el pj
{
    _buffo=_mapa->getbuffo();
    if(_pj->siColisiona(*_buffo))
    {
        //cout<<endl<<"TOCO BUFFO :"<<_buffo.getTocoBuffo();
        cout<<endl<<"ESTADO     :"<<_buffo->getEstado();
        _buffo->setEstado(false);
        _pj->setChupoFernet(true);
    }
}

void Gameplay::chequearColisionPuerta()
{

    if(_mapa->getPuerta()->siColisiona(*_pj)){
        if(_cantE<=0 && _puerta->getEstado()==true)
        {
            cout<<endl<<"COLISIONA CON PUERTA";
            _levelUp=true;
        }else{
            cout << "NO HABILITADA AUN" << endl;
        }
    }
}

void Gameplay:: resetLevel(){
    pMuertePJ = new PantallaMuerte(_resolucion.x,_resolucion.y);
    while(pMuertePJ->getEstado()==true){
        pMuertePJ->update();
        _window->clear();
        _window->draw(*pMuertePJ);
        _window->display();
    }
    delete pMuertePJ;

    ///REARMAR MAPA Y POSICIONAR TODO NUEVAMENTE
    armarNivel(_nivel);

}

void Gameplay::armarNivel(int lvl){
    _bomba=new Bomba(); ///inicializa la bomba
    _bombaActiva=false; ///estado de bomba en el mapa
    _explosion=new Explosion[2];///inicializa explosion 0=Horizontal, 1=Vertical
    _explosion[1].rotar();
    ///MAPA
    _mapa = new Mapa(*_window);
    _cantBloques = _mapa->getCantBloques();
    _bloque=new Bloques;
    _buffo=new Buffos;
    _puerta=new Puerta;
    ///ENEMIGOS
    _cantE=5+rand()%5;///random entre 5 y 10
    cout << _cantE << endl;
    _enemigosActivos=_cantE;
    _vEnemigos = new Enemigo[_cantE];///cantidad de enemigos
    posAnteriorEnemigo = new sf::Vector2f[_cantE]; ///vector para posiciones de enemigos
    for(int i=0;i<_cantE;i++)
    {
        sf::Vector2f posE(_mapa->posicionarEnemigos(i));
        _vEnemigos[i].respawn(posE);///ubica al enemigo en el mapa
    }


    _mapa->mostrar();///muestra las matrices
    pantallaDelNivel= new PantallaNivel(600,450,1);
    while(pantallaDelNivel->getEstado()==true){
        pantallaDelNivel->update();
        _window->clear();
        _window->draw(*pantallaDelNivel);
        _window->display();
    }
    delete pantallaDelNivel;
}

void Gameplay::renderizar(){///en esta funcion va todos los draw
    _window->clear();
    ///----DRAW-----
    _window->draw(*_mapa);
    if(_bomba->getEstado()==true)
    {
        _window->draw(*_bomba);
    }
    for(int i=0;i<2;i++){
        if(_explosion[i].getExplosion()==true)
        {
            _window->draw(_explosion[i]);
        }
    }
    _window->draw(*_vidasPJ);
    _window->draw(*_puntajePJ);
    _window->draw(*_pj);
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

bool Gameplay::getLevelUp(){
    return _levelUp;
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
    _buffo->guardarBuffos();
    _puerta->guardarPuerta();
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
    _buffo->cargarBuffos(1);
    _puerta->cargarPuerta(1);
}

Gameplay::~Gameplay(){
    delete _evento;
    delete _window;
    delete _pj;
    delete _vidasPJ;
    delete[] _vEnemigos;
    delete _mapa;
    delete _bomba;
    delete[] _explosion;
    delete _bloque;
    delete[] posAnteriorEnemigo;
    delete _buffo;
    delete _puerta;
}
