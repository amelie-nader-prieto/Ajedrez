#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Alfil :
    public Pieza
{
public:
    SpriteSequence spriteAlfilN{ "bin/imagenes/AlfilNegro.png", 1 };
    SpriteSequence spriteAlfilB{ "bin/imagenes/AlfilBlanco.png", 1 };// No son las piezas finales, es solo para probar como se dibujan
    Alfil(int fila, int columna,Jugador j=B);
    void dibuja();
};
