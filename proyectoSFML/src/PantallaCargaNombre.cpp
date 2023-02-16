#include "PantallaCargaNombre.h"

PantallaCargaNombre::PantallaCargaNombre(sf::RenderWindow &ventana)
{
    _ventana= &ventana;
    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "Error al leer la fuente"<< endl;
    }

    _text.setFont(_font);
    _text.setFillColor(sf::Color::Yellow);
    _text.setCharacterSize(30);


    _estado=true;
}

PantallaCargaNombre::~PantallaCargaNombre()
{
    //dtor
}

bool PantallaCargaNombre::getEstado(){
    return _estado;
}

void PantallaCargaNombre::cargarNombre(){
    string nombre;
    while (!_estado)
    {
        // Handle events
        sf::Event event;
        while (_ventana->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _ventana->close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8 && _text.getString().getSize() > 0)
                {
                    // Backspace
                    nombre = _text.getString();
                    nombre.pop_back();
                    _text.setString(nombre);
                }
                else if (event.text.unicode == 13)
                {
                    // Enter
                     nombre = _text.getString();
                    // Do something with the nickname
                    _estado=true;
                }
                else if (event.text.unicode < 128)
                {
                    // Add a character
                     nombre = _text.getString();
                    nombre += static_cast<char>(event.text.unicode);
                    _text.setString(nombre);
                }
            }
        }

        // Clear the window
        _ventana->clear();

        // Draw the text
        _ventana->draw(_text);

        // Display the window
        _ventana->display();
    }

    _nombre= nombre;
}

string PantallaCargaNombre::getNombre(){
    return _nombre;
}

void PantallaCargaNombre::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_nombre,states);

}
