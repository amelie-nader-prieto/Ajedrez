#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"

class Peon :
    public Pieza
{
public:
    Peon(int fila, int columna,Jugador j=B);
  
    SpriteSequence spriteN{ "bin/imagenes/peon-negro.png", 1 };
    SpriteSequence spriteB{ "bin/imagenes/peon-blanco.png", 1 };

    void dibuja();
};

