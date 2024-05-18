#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Alfil :
    public Pieza
{
public:
    Alfil(int fila, int columna,Jugador j=B);

    SpriteSequence spriteN{ "bin/imagenes/alfil-negro.png", 1 };
    SpriteSequence spriteB{ "bin/imagenes/alfil-blanco.png", 1 };

    void dibuja();
};
