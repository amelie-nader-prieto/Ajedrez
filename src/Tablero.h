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
	Tanto las funciones lógicas como las de dibujo accederán SÓLO a este dato.
	Con lo que hay en este dato basta para gestionar todo
	*/

	// constructor
	Tablero();

	// operador para indexar con un vector
	inline Pieza* operator[](const Vector2D& posicion)const {
		return tablero[posicion.x][posicion.y];
	}


	void mover_pieza(Vector2D p_ini, Vector2D p_fin);
	void activar_captura(Vector2D _posicion);
	void activar_promocion(Vector2D _posicion);
	void activar_promocion(Vector2D _posicion, Tipo nuevo_tipo);
	void borrar_pieza_capturada(Jugador _jugador);


	// Funciones de prueba
	/* Estas funciones son para hacer pruebas mientras desarrollamos.
	* NO SE USAN durante la partida.
	*/

	/* Vacía el tablero y borra las piezas */
	void vaciar();
	/* Para crear una pieza cualquiera en una casilla cualquiera */
	void crear_pieza(Tipo _tipo, Jugador _jugador, Vector2D _posicion);
	/* Devuelven una copia de los datos privados de la clase.
	* Las uso para comprobar si todos los datos se actualizan correctamente
	*/
	inline auto get_piezas_bla() { return piezas_bla; }
	inline auto get_piezas_neg() { return piezas_neg; }



	void cambiarTurno() { //Solo para probar si cambia de turno, después borrar
		//es solo para las pruebas de movimiento
		turnoActual = (turnoActual == W) ? B : W;
	}

	void dibujaPiezas(); //aun por ver en donde va
};

