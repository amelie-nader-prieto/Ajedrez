#pragma once
#include "Casilla.h"
#define Filas 10
#define Columnas 11
//clase que funciona como interf�z gr�fica
//para mostrar el tablero y las piezas
class GLTablero
{
public:
	Casilla cas;
	void dibuja();
};

