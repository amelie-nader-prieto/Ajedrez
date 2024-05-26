#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"
#include "Tablero.h"


class Peon : public Pieza
{
    
    
public:
    Peon(int fila, int columna,Jugador j);
    bool en_captura;
    bool posible_captura_al_paso(Peon p);

    void cuando_en_captura();
};

