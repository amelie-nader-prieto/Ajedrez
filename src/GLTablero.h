#pragma once
#include "Casilla.h"
#define Filas 10
#define Columnas 11
//clase que funciona como interfáz gráfica
//para mostrar el tablero y las piezas
class GLTablero
{
public:
	Casilla cas;
	void dibuja();
};

