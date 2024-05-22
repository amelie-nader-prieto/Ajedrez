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

#define FILA 10
#define COLUMNA 11

using std::vector;

class Tablero
{
	friend static void iniciar(Tipo tipo, Vector2D posicion, Jugador j, Tablero tab);

	Pieza ninguna;
	vector<Pieza>piezas_bla{};
	vector<Pieza>piezas_neg{};

public:
	Pieza* tablero[FILA][COLUMNA] = { nullptr }; /* Esto es como la interfaz.
	Tanto las funciones lógicas como las de dibujo accederán SÓLO a este dato.
	Con lo que hay en este dato basta para gestionar todo
	*/

	// constructor
	Tablero();

	void mover_pieza(Vector2D p_ini, Vector2D p_fin);
	void mover_pieza(Pieza _p, Vector2D p_fin);
	void activar_captura(Vector2D _posicion);
	void borrar_pieza_capturada(Jugador _jugador);

	// Funciones de prueba
	/* Estas funciones las uso para hacer pruebas.
	* NO SE USAN durante la partida
	*/
	/* Vacía el tablero y borra las piezas */
	void vaciar();
	/* Para crear una pieza cualquiera en una casilla cualquiera */
	void crear_pieza(Tipo _tipo, Jugador _jugador, Vector2D _posicion);

};