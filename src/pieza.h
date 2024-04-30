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
	// Las defino aquí porque me salen errores de enlazado si no
	Vector2D GetPosicion() { return direccion; }
	Tipo GetTipo() { return tipo; }
	int GetFila() { return fila; }
	int GetColumna() { return columna; }
	Jugador GetJugador() { return jugador; }
	
	void SetFila(int _fila) { fila = _fila; }
	void SetColumna(int _columna) { columna = _columna; }
	void SetTipo(Tipo t) { tipo = t; }
	void SetJugador(Jugador j) { jugador = j; }

};

