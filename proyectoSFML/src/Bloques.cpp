#include "Bloques.h"
Bloques::Bloques(){
}
Bloques::Bloques(int t, sf::Vector2f pos)
{
    _tipo=t;

    _pos=pos;

    if(!_text.loadFromFile("bloques.png")){
        cout << "No se pudo cargar mapSpritesheet" << endl;
    }
    cout << _pos.x << " " << _pos.y << endl;
    sf::Vector2u tileSize(35,30);

    _sprite.setTexture(_text);
    _sprite.setTextureRect({0,0,36,30});
    _sprite.setPosition(_pos.x+1+36,_pos.y+1+30);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2,_sprite.getGlobalBounds().height/2);
    /*
    ///vertex array
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(15*15*16);



    int tu=_tipo%(m_tileset.getSize().x/35);
    int tv=_tipo/(m_tileset.getSize().x/35);
    sf::Vertex* quad =&m_vertices[(_pos.x+_pos.y*35)*4];
    ///definir las 4 esquinas
    quad[0].position = sf::Vector2f(_pos.x * tileSize.x, _pos.y * tileSize.y);
    quad[1].position = sf::Vector2f((_pos.x + 1) * tileSize.x, _pos.y * tileSize.y);
    quad[2].position = sf::Vector2f((_pos.x + 1) * tileSize.x, (_pos.y + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(_pos.x * tileSize.x, (_pos.y + 1) * tileSize.y);

    ///definir las cordenadas de la textura
    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
*/
}

void Bloques::setEstado(bool es){
    _estado=es;
}

sf::Vector2f Bloques::getPos(){
    return _pos;
}

void Bloques::draw(sf::RenderTarget& target,sf::RenderStates states)const //dibuja al enemigo
{
    target.draw(_sprite,states);
}


sf::FloatRect Bloques::getBounds() const
{
    return _sprite.getGlobalBounds();
}
