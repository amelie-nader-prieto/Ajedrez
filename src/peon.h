#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Peon :
    public Pieza
{
public:
    SpriteSequence spritePeonN{"bin/imagenes/PeonNegro.png", 1};
    SpriteSequence spritePeonB{"bin/imagenes/PeonBlanco.png", 1};// No son las piezas finales, es solo para probar como se dibujan


    Peon(int fila, int columna,Jugador j=B);
    void dibuja();
};

