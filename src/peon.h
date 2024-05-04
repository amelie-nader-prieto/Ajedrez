#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Peon :
    public Pieza
{
public:
    SpriteSequence spritePeonN{"bin/imagenes/peonN.png", 1};
    SpriteSequence spritePeonB{"bin/imagenes/peonB.png", 1};

    Peon(int fila, int columna,Jugador j=B);
    void dibuja();
};

