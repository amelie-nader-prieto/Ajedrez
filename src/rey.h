#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Rey :
    public Pieza
{
public:
    Rey(int fila, int columna,Jugador j=B);

    //SpriteSequence spriteN{ "bin/imagenes/rey-negro.png", 1 };
    //SpriteSequence spriteB{ "bin/imagenes/rey-blanco.png", 1 };

    void dibuja(int);
};

