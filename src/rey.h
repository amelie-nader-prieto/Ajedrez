#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Rey :
    public Pieza
{
public:
    SpriteSequence spriteReyN{ "bin/imagenes/ReyNegro.png", 1 };
    SpriteSequence spriteReyB{ "bin/imagenes/ReyBlanco.png", 1 };// No son las piezas finales, es solo para probar como se dibujan
    Rey(int fila, int columna,Jugador j=B);
    void dibuja();
};

