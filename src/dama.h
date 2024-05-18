#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Dama :
    public Pieza
{
public:
    Dama(int fila, int columna,Jugador j=B);

    SpriteSequence spriteN{ "bin/imagenes/dama-negro.png", 1 };
    SpriteSequence spriteB{ "bin/imagenes/dama-blanco.png", 1 };

    void dibuja();
};

