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
	Pieza() = default;
	Pieza(int fila, int columna, Tipo t): fila(fila), columna (columna), tipo (t){}

	// Funciones de interfaz
	Vector2D GetPosicion();
	Tipo GetTipo();
	int GetFila();
	int GetColumna();
	Tipo GetTipo();
	Jugador GetJugador();
	
	void SetFila(int);
	void SetColumna(int);
	void SetTipo(Tipo);
	void SetJugador(Jugador);

};

