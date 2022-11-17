#include "MainMenu.h"
#include "Aplicacion.h"
#include "Librerias.h"

int main()
{
    std::srand((unsigned)std::time(0));
    Aplicacion * app=new Aplicacion(sf::Vector2u(720,450));

    return 0;
}
