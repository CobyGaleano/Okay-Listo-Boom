#include "Partida.h"

Partida::Partida()
{
    //ctor
}
bool Partida::guardarPartida(){
    FILE *p;
    p=fopen("Partidas.dat","ab");
    if(p==NULL) return false;
    bool escribio = fwrite(this, sizeof (Partida), 1, p);
    fclose(p);
    return escribio;
}
bool Partida::cargarPartida(int pos){
    FILE *p;
    p=fopen("Partidas.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos * sizeof (Partida), 0);
    bool leyo = fread(this, sizeof (Partida), 1, p);
    fclose(p);
    return leyo;
}
