#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Caballo :
    public Pieza
{
public:
    SpriteSequence spriteCaballoN{ "bin/imagenes/CaballoNegro.png", 1 };
    SpriteSequence spriteCaballoB{ "bin/imagenes/CaballoBlanco.png", 1 };
    Caballo(int fila, int columna,Jugador j=B);

    void dibuja();
};
