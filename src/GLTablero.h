#pragma once
#include "Casilla.h"
#define FILA 10
#define COLUMNA 11
//clase que funciona como interf�z gr�fica
//para mostrar el tablero y las piezas
class GLTablero
{
public:
	Casilla cas;
	void dibuja();
};

