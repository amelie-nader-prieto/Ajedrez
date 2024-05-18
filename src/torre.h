#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Torre :
    public Pieza
{
public:
    Torre(int fila, int columna,Jugador j=B);

    SpriteSequence spriteN{ "bin/imagenes/torre-negro.png", 1 };
    SpriteSequence spriteB{ "bin/imagenes/torre-blanco.png", 1 };

    void dibuja();
};
