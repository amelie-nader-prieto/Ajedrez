#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Caballo :
    public Pieza
{
public:
    Caballo(int fila, int columna,Jugador j=B);

    SpriteSequence spriteN{ "bin/imagenes/caballo-negro.png", 1 };
    SpriteSequence spriteB{ "bin/imagenes/caballo-blanco.png", 1 };

    void dibuja();
};
