#pragma once
#include "pieza.h"
#include "Tipos_piezas.h"


#include "Tablero.h"
#include <iostream>

#include "LogicaAjedrez.h"

class Alfil :
    public Pieza
{
public:
    Alfil(int fila, int columna,Jugador j=B);
   

   // vector <Vector2D> obtener_posibles_movimientos (Tablero tab);


};
