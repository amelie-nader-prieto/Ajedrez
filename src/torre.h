#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Torre :
    public Pieza
{
public:
    Torre(int fila, int columna,Jugador j=B);
};
