#ifndef RANKING_H
#define RANKING_H
#include "../Librerias.h"
#include <SFML/Graphics.hpp>

class Ranking: public sf::Drawable
{
    public:
        Ranking();
        Ranking(sf::Vector2u resolucion);
        ~Ranking();

        bool getEstado();
        void update();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const;
    private:
        sf::Text _titulo;
        sf::Font _font;

        bool _estado;

        sf::Sprite _logo;
        sf::Texture _logoTexture;


};

#endif // RANKING_H
