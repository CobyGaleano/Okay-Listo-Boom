#include "MainMenu.h"

MainMenu::MainMenu(){
    ///ctor

}

MainMenu::MainMenu(float ancho,float alto)
{
    if(!_font.loadFromFile("BOMBERMA.TTF"))
    {
        cout << "error"<< endl;
    }
    _menu[0].setFont(_font);
    _menu[0].setFillColor(sf::Color::White);
    _menu[0].setString("PLAY");
    _menu[0].setCharacterSize(50);
    _menu[0].setPosition(sf::Vector2f(ancho/2-150,alto/(CANT_ITEMS+1)*1));

    _menu[1].setFont(_font);
    _menu[1].setFillColor(sf::Color::White);
    _menu[1].setString("OPCIONES");
    _menu[1].setCharacterSize(50);
    _menu[1].setPosition(sf::Vector2f(ancho/2-150,alto/(CANT_ITEMS+1)*2));

    _menu[2].setFont(_font);
    _menu[2].setFillColor(sf::Color::White);
    _menu[2].setString("RANKING");
    _menu[2].setCharacterSize(50);
    _menu[2].setPosition(sf::Vector2f(ancho/2-150,alto/(CANT_ITEMS+1)*3));

    _menu[3].setFont(_font);
    _menu[3].setFillColor(sf::Color::White);
    _menu[3].setString("EXIT");
    _menu[3].setCharacterSize(50);
    _menu[3].setPosition(sf::Vector2f(ancho/2-150,alto/(CANT_ITEMS+1)*4));

    _selected=1;
}

void MainMenu::cmd()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        _state=ARRIBA;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        _state=ABAJO;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        _state=SELECT;
    }
}

void MainMenu::update(){
    _menu[_selected-1].setFillColor(sf::Color::White);
    if(_state==ARRIBA){
        _selected--;
        if(_selected<1){
            _selected=1;
        }
        _state=WAITING;
    }
    if(_state==ABAJO){
        _selected++;
        if(_selected>CANT_ITEMS){
            _selected=CANT_ITEMS;
        }
        _state=WAITING;
    }
    _menu[_selected-1].setFillColor(sf::Color::Blue);

}

void MainMenu::draw(sf::RenderWindow& window)
{
    for(int i=0; i<CANT_ITEMS; i++)
    {
        window.draw(_menu[i]);
    }
}

bool MainMenu::getState(){
    if(_state==SELECT){
        _state=WAITING;
        return true;
    }
    return false;
}

int MainMenu::getSelected(){
    return _selected;
}
MainMenu::~MainMenu()
{
}
