#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Dama :
    public Pieza
{
public:
    SpriteSequence spriteReinaN{ "bin/imagenes/ReinaNegro.png", 1 };
    SpriteSequence spriteReinaB{ "bin/imagenes/ReinaBlanco.png", 1 };
    Dama(int fila, int columna,Jugador j=B);

    void dibuja();
};
