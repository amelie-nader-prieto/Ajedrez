#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Dama :
    public Pieza
{
public:

    Dama(int fila, int columna,Jugador j=B);

    void dibuja(int);
};
