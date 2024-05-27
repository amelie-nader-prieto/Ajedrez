#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Rey :
    public Pieza
{
public:
   
    Rey(int fila, int columna,Jugador j=B);
    void dibuja(int skin);
};

