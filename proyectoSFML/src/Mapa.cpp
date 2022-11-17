#include "Mapa.h"

Mapa::Mapa(){
}
Mapa::Mapa(sf::RenderWindow &window)
{
    srand(time(0));

    ///0= espacio transitable
    ///1= bloque no destruible
    ///2= bloque destruible

    _ventana= &window;

    ///arma la matriz que ubicara los bloques en el mapa
    for(int i=0; i<CANT_FILAS; i++)
    {
        for(int j=0; j<CANT_COLUMNAS; j++)
        {
            if(i==0||i==14||j==0||j==14)
            {
                _matriz[i][j]=1;
            }
            else
            {
                if(i==1&&j==1||i==2&&j==1||i==1&&j==2)
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
}

void Mapa::update(){
    for(int i=0;i<_cantB;i++){
        if(_vBloques[i].getEstado()==false && _vBloques[i].getTipo() == 2){
            _matriz[(int)_vBloques[i].getPos().x][(int)_vBloques[i].getPos().y]=0;
        }
    }
}

sf::Vector2f Mapa::posicionarEnemigos(int enemigo){
    for(int j=rand()%CANT_FILAS; j<CANT_FILAS; j++)
    {
        for(int i=rand()%CANT_COLUMNAS; i<CANT_COLUMNAS; i++)
        {
            if(_matriz[i][j]==0&&(i!=1&&j!=1||i!=2&&j!=1||i!=1&&j!=2)){
                bool hayBloque=false;
                for(int x=0;x<_cantB;x++){
                    if(_vBloques[x].getPos().x==i&& _vBloques[x].getPos().y==j){
                        hayBloque==true;
                    }
                }
                if(!hayBloque){
                    sf::Vector2f pos(i,j);
                    return pos;
                }
            }
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
}
