#pragma once
#ifndef PARTIDA_H
#define PARTIDA_H
#include <cstring>
#include "Gameplay.h"


class Partida: public Gameplay
{
    private:


    public:
        Partida();
        bool guardarPartida();
        bool cargarPartida(int pos);

        bool operator=(Gameplay &gp);
};

#endif // PARTIDA_H
