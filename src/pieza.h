#pragma once
#include "Tipos_piezas.h"
#include "vector2D.h"

class Pieza
{
protected:
	int fila;
	int columna;
	Tipo tipo;
	Jugador jugador;

	Vector2D direccion{ fila,columna };

public:
	Pieza(int fila, int columna, Tipo t): fila(fila), columna (columna), tipo (t){}

	Vector2D GetPosicion();
	Tipo GetTipo();
};

