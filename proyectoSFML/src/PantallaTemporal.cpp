#include "PantallaTemporal.h"

PantallaTemporal::PantallaTemporal(){

}
void PantallaTemporal::Armar(int fSize,string nombreArch,string titulo,int duracion,POSICION pos, float ancho, float alto){
    _estado=true;

    ///carga de la fuente
    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "Error al leer la fuente"<< endl;
    }
    ///carga del logo de la pantalla
    _archivoLogo=nombreArch+".png";
    if(!_logoTexture.loadFromFile(_archivoLogo)){
        cout << "Error al leer textura" << endl;
    }

    _titulo.setFont(_font);
    _titulo.setFillColor(sf::Color::Yellow);
    _titulo.setCharacterSize(fSize);
    _titulo.setString(titulo);

    _logo.setTexture(_logoTexture);
    ///Seteo de la posicion del logo segun el valor recibido:
    _posicionLogo=pos;
    _anchoP=ancho;
    _altoP=alto;
    switch(_posicionLogo){
        case ARRIBA_CENTRO:{
            _logo.setOrigin(_logo.getGlobalBounds().width/2,0);
            _logo.setPosition(sf::Vector2f(_anchoP/2,0));
        }
        break;
        case ARRIBA_IZQUIERDA:{
            _logo.setOrigin(_logo.getGlobalBounds().width/2,_logo.getGlobalBounds().height/2);
            _logo.setPosition(sf::Vector2f(_anchoP/2,(_altoP-_logo.getGlobalBounds().height*1.5)));
        }
        break;
        case ABAJO_CENTRO:{
            _logo.setOrigin(_logo.getGlobalBounds().width/2,_logo.getGlobalBounds().height/2);
            _logo.setPosition(sf::Vector2f(_anchoP/2,_altoP));
        }
        break;
        case CENTRO:{
            _logo.setOrigin(_logo.getGlobalBounds().width/2,_logo.getGlobalBounds().height/2);
            _logo.setPosition(_anchoP/2,_altoP/2);
        }
        break;
    }
        _duracion=duracion;
        _tiempo=0;
}

void PantallaTemporal:: update(){
    _tiempo++;
    if(_tiempo == _duracion){
        _estado=false;
        _tiempo=0;
        cout << "PASO POR ACA" << endl;
    }
}

bool PantallaTemporal::getEstado(){
    return _estado;
}

void PantallaTemporal::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
    target.draw(_logo,states);
    target.draw(_titulo,states);
}
PantallaTemporal::~PantallaTemporal(){

}
