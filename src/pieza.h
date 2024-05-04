#pragma once
#include "Tipos_piezas.h"
#include "vector2D.h"
#include "ETSIDI.h"
#include "freeglut.h"

using ETSIDI::SpriteSequence; //facilita el uso de texturas, fuentes y sonidos

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
	Pieza(int fila, int columna, Tipo t,Jugador j=B) : fila(fila), columna(columna), tipo(t), jugador(j) {}

	// Funciones de interfaz
	Vector2D GetPosicion();
	Tipo GetTipo();
	int GetFila();
	int GetColumna();
	Jugador GetJugador();
	
	void SetFila(int _fila);
	void SetColumna(int _columna);
	void SetTipo(Tipo t);
	void SetJugador(Jugador j);

	//virtual void dibuja() = 0;
};
