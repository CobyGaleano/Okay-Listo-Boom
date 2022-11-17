#ifndef PARTIDA_H
#define PARTIDA_H


class Partida
{
    private:
        char usuario[30];

    public:
        Partida();
        bool guardarPartida();
        bool cargarPartida();

        void operator=(Aplicacion &obj);
};

#endif // PARTIDA_H
