#pragma once
#include "Casilla.h"
#include "ETSIDI.h"
#define FILA 10
#define COLUMNA 11
//clase que funciona como interfáz gráfica
//para mostrar el tablero y las piezas
class GLTablero
{
public:
	Casilla cas;
	void dibuja();
};

