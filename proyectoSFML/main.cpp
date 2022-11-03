#include "Librerias.h"

int main()
{
    std::srand((unsigned)std::time(0));
    Mapa m;
    m.mostrar();
    // Inicializador de la ventana
    sf::RenderWindow window(sf::VideoMode(525,450), "CompuMundoHiperMegaDev");
    window.setFramerateLimit(75);

   //declaracion de personajes
    Personaje bomber;
    Enemigo enemy;
    enemy.respawn();



    //GAME LOOP (update del juego)
    while (window.isOpen())
    {

        // Read InPut: Atualizar los estados de los perifericos de entrada
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //CMD - Joy
        bomber.cmd();

        //Update - Actualiza los estados del juego
        bomber.update();
        enemy.update();

        if (bomber.siColisiona(enemy))
        {
            bomber.muere();
        }


        window.clear();

        //Draw - Dibuja en la pantalla
        window.draw(m);
        window.draw(bomber);
        window.draw(enemy);






        //Display - Flip
        window.display();

    }

    //Liberacion del juego

    return 0;
}
