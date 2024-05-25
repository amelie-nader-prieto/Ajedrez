#pragma once

#include "pieza.h"
#include "alfil.h"
#include "caballo.h"
#include "dama.h"
#include "peon.h"
#include "rey.h"
#include "torre.h"
#include "No_pieza.h"
#include <vector>
#include <iostream>

#define FILA 10
#define COLUMNA 11

using std::vector;

class Tablero
{
	friend static void iniciar(Tipo tipo, Vector2D posicion, Jugador j, Tablero tab);

	Pieza ninguna;
	vector<Pieza>piezas_bla{};
	vector<Pieza>piezas_neg{};

	Jugador turnoActual; //Variable para gestionar el turno actual en la partida 

public:
	Pieza* tablero[FILA][COLUMNA] = { nullptr }; /* Esto es como la interfaz.
	Tanto las funciones l�gicas como las de dibujo acceder�n S�LO a este dato.
	Con lo que hay en este dato basta para gestionar todo
	*/

	// constructor
	Tablero();

	void mover_pieza(Vector2D p_ini, Vector2D p_fin);
	void activar_captura(Vector2D _posicion);




	void dibujaPiezas();
	void cambiarTurno() { //Solo para probar si cambia de turno, despues borrar
		//es solo para las pruebas de movimiento
		turnoActual = (turnoActual == W) ? B : W;
	}

};

