#include "Mapa.h"

Mapa::Mapa(){
}
Mapa::Mapa(sf::RenderWindow &window)
{
    srand(time(0));

    ///0= espacio transitable
    ///1= bloque no destruible
    ///2= bloque destruible
    ///3= se posicionara la puerta
    ///4= se posiciono un enemigo
    ///5= se posicionara un buffo

    _ventana= &window;

    ///arma la matriz que ubicara los bloques en el mapa
    for(int i=0; i<CANT_FILAS; i++)
    {
        for(int j=0; j<CANT_COLUMNAS; j++)
        {
            if(i==0||i==14||j==0||j==14)
            {
                _matriz[i][j]=1;///bloque indestructible - bordes
            }
            else
            {
                if((i==1&&j==1)||(i==2&&j==1)||(i==1&&j==2))
                {
                    ///espacio vacio zona spawn
                    _matriz[i][j]=0;
                }
                else if(i%2==0&&j%2==0)
                {
                    ///bloques indestructibles
                    _matriz[i][j]=1;
                }
                else
                {
                    ///sectores que iran al azar
                    _matriz[i][j]=2;
                }
            }
        }
    }
    ///pone los bloques destructibles al azar o deja espacios vacios
    for(int i=0;i<CANT_FILAS;i++){
        for(int j=0;j<CANT_COLUMNAS;j++){
            if(_matriz[i][j]==2){
                int n=rand();
                if(n%2==0){
                    ///espacios vacios >> transitables
                    _matriz[i][j]=0;
                }
            }
            if(_matriz[i][j]!=0){
                _cantB++;
            }
        }
    }
    copiarMatriz();
    mostrar();

    ///armar vector de bloques
    cout << "Cantidad de Bloques: " << _cantB << endl;
    _vBloques = new Bloques[_cantB];

    ///leer el tileset
    if(!m_tileset.loadFromFile("Fondo.png")){
        cout << "No se pudo cargar mapSpritesheet" << endl;
    }

    sf::Vector2u tileSize(35,30);

    ///vertex array
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(15*15*16);

    ///cargar el array un quad por tile
    int p=0;
    for(int i=0;i<CANT_FILAS;i++){
        for(int j=0;j<CANT_COLUMNAS;j++){
            int tilenumber;
            if(_matriz[i][j]!=0){
                tilenumber=_matriz[i][j];

                sf::Vector2f pos(i,j);
                _vBloques[p++].armar(tilenumber,pos);

            }
            tilenumber=0;


            int tu=tilenumber%(m_tileset.getSize().x/35);
            int tv=tilenumber/(m_tileset.getSize().x/35);
            sf::Vertex* quad =&m_vertices[(i+j*35)*4];
            ///definir las 4 esquinas
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            ///definir las cordenadas de la textura
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    ///inicializar buffo y puerta
    cout << "aca" << endl;
    _buffo1=new Buffos();
    _buffo1->setPos(posicionarBuffo());//posiciona el buffo dentro de un bloque
    _buffo1->respawn();
    _puerta1=new Puerta();
    _puerta1->setPos(posicionarPuerta());
    _puerta1->respawn();
}

void Mapa::mostrar()
{
    for(int j=0; j<CANT_FILAS; j++)
    {
        for(int i=0; i<CANT_COLUMNAS; i++)
        {
            cout << _matriz[i][j] << " " ;
        }
        cout << endl;
    }

    cout << "Matriz copiada para posiciones: " << endl;
    for(int j=0; j<CANT_FILAS; j++)
    {
        for(int i=0; i<CANT_COLUMNAS; i++)
        {
            cout << _matrizPosiciones[i][j] << " " ;
        }
        cout << endl;
    }
}

void Mapa::update(){
    for(int i=0;i<_cantB;i++){
        if(_vBloques[i].getEstado()==false && _vBloques[i].getTipo() == 2){
            _matriz[(int)_vBloques[i].getPos().x][(int)_vBloques[i].getPos().y]=0;
        }
    }
}

/*sf::Vector2f Mapa::posicionarEnemigos(int enemigo){
    bool hayBloque=false;
//        for(int j=rand()%CANT_FILAS; j<CANT_FILAS; j++)
            for(int j=1; j<CANT_FILAS; j++)
        {
                sf::Vector2f pos(0,0);
                    int iRan=rand()%CANT_COLUMNAS;

                    for(int i=rand()%CANT_COLUMNAS; i<CANT_COLUMNAS; i++)
                    {
                            if(_matriz[i][j]==0&&_matriz[i][j]!=1&&_matriz[i][j]!=2/*&&j!=0&&i!=0&&i!=14&&j!=14&&(i!=1&&j!=1)
                               &&(i!=2&&j!=1)&&(i=!1&&j!=2)){
                                for(int x=0;x<_cantB;x++){
                                    if(_vBloques[x].getPos().x==i&& _vBloques[x].getPos().y==j){
                                        hayBloque==true;
                                    }
                                    if(!hayBloque){
                                        pos.x=j;
                                        pos.y=i;
                                        cout<<pos.x<<" "<<pos.y<<endl;
                                        cout<<"encontro posicion"<<endl;
                                        return pos;
                                    }
                                }
                            }
                    }

        }

}*/

sf::Vector2f Mapa::posicionarEnemigos(int enemigo){

    for(int j=rand() % 13 + 1; j<CANT_FILAS; j++)
    {
        for(int i=rand() % 13 + 1; i<CANT_COLUMNAS; i++)
        {
            bool hayBloque=false;
            bool hayEnemigo=false;
            if(_matrizPosiciones[i][j]==0&&(i!=1&&j!=1)&&(i!=2&&j!=1)&&(i!=1&&j!=2)&&i!=0&&i!=14&&i!=14&&j!=0){

                if(_matrizPosiciones[i][j]==4){
                    hayEnemigo=true;
                }
                if(_matrizPosiciones[i][j]==1||_matrizPosiciones[i][j]==2){
                    hayBloque=true;
                }
                /*for(int x=0;x<_cantB;x++){
                    if(_vBloques[x].getPos().x==i&& _vBloques[x].getPos().y==j){
                        hayBloque=true;
                    }
                }*/
                if(!hayBloque && !hayEnemigo){
                    sf::Vector2f pos(i,j);
                    _matrizPosiciones[i][j]=4;
                    return pos;
                }
            }
        }
    }
}

sf::Vector2f Mapa::posicionarPuerta(){
    sf::Vector2f pos(0,0);

    while(pos.x==0&&pos.y==0){
        int a=rand() % 13 + 1;
        int b=rand() % 13 + 1;
        if(a!=0 && a!=14 && b!=0 && b!=14){
            if(_matrizPosiciones[a][b]!=0 && _matrizPosiciones[a][b]!=1 && _matrizPosiciones[a][b]!=4 && _matrizPosiciones[a][b]!=5){
                pos.x=a;
                pos.y=b;
                _matrizPosiciones[a][b]=3;
            }
        }
    }
    return pos;
}

sf::Vector2f Mapa::posicionarBuffo(){
    sf::Vector2f pos(0,0);

    while(pos.x==0&&pos.y==0){
        int a=rand() % 13 + 1;
        int b=rand() % 13 + 1;
        if(a!=0 && a!=14 && b!=0 && b!=14){
            if(_matrizPosiciones[a][b]!=0 && _matrizPosiciones[a][b]!=1 && _matrizPosiciones[a][b]!=4 && _matrizPosiciones[a][b]!=3){
                pos.x=a;
                pos.y=b;
                _matrizPosiciones[a][b]=5;
            }
        }
    }
    return pos;
}

void Mapa::copiarMatriz(){
    for(int i=0;i<CANT_FILAS;i++){
        for(int j=0;j<CANT_COLUMNAS;j++){
            _matrizPosiciones[i][j]=_matriz[i][j];
        }
    }
}

int Mapa::getCantBloques(){
    return _cantB;
}

Bloques* Mapa::getBloque(int pos){
    Bloques * bloq=&_vBloques[pos];
    return bloq;
}



bool Mapa::guardarMapa(){
    FILE *p;
    p=fopen("Mapa.dat","wb");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Mapa), 1, p);
    fclose(p);
    for(int i=0;i<_cantB;i++){
        _vBloques[i].guardarBloques(i);
    }
    return escribio;
}
bool Mapa::cargarMapa(int pos){
    FILE *p;
    p=fopen("Mapa.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Mapa), 0);
    bool leyo = fread(this, sizeof (Mapa), 1, p);
    fclose(p);
    for(int i=0;i<_cantB;i++){
        _vBloques[i].cargarBloques(i);
    }
    return leyo;
}


Mapa::~Mapa()
{
    delete[] _vBloques;
    delete _buffo1;
    delete _puerta1;
}
