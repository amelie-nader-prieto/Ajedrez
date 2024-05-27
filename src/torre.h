#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Torre :
    public Pieza
{
public:
    SpriteSequence spriteTorreN{ "bin/imagenes/TorreNegro.png", 1 };
    SpriteSequence spriteTorreB{ "bin/imagenes/TorreBlanco.png", 1 };
    Torre(int fila, int columna,Jugador j=B);

    void dibuja();
};
