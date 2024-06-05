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

using std::vector; using std::cout;


// OPERADORES

/* Operador para imprimir el tipo de pieza */
inline std::ostream& operator<<(std::ostream& co, const Tipo& t) {
	switch (t) {
	case no_hay:co << " "; break;
	case R:co << "R"; break;
	case D:co << "D"; break;
	case C:co << "C"; break;
	case A:co << "A"; break;
	case T:co << "T"; break;
	case P:co << "P"; break;
	default:break;
	}

	return co;

}
/* Operador para imprimir el color de la pieza */
inline std::ostream& operator<<(std::ostream& co, const Jugador& _jugador) {

	switch (_jugador) {
	case B:co << "n"; break; // negro
	case W:co << "b"; break; // blanco
	default:break;
	}

	return co;

}
/* Operador para representar una casilla con número y letra */
inline std::ostream& operator<<(std::ostream& co, const Vector2D& _casilla) {

	vector<char>letras_columnas = { 'a','b','c','d','e','f','g','h','i','j','k' };
	int num_fila_0 = 10;
	co << letras_columnas.at(_casilla.y) << num_fila_0 - _casilla.x;

	return co;

}
/* operador para imprimir toda la info de la pieza
(Imprime tipo, color y casilla en la que está) */
inline std::ostream& operator<<(std::ostream& co, Pieza& _pieza) {
	if (_pieza.GetTipo() == no_hay) return co;
	co << (_pieza.GetTipo()) << (_pieza.GetJugador()) << " en " << (_pieza.GetPosicion());
	if (_pieza.GetCapturada()) co << " (capturada)";
	else if (_pieza.GetPromocionado())co << "(promocionado)";
	//else co << "       ";
	return co;
}

class Tablero
{
	
	Pieza ninguna; // este objeto simboliza la ausencia de pieza en una casilla
	vector<Pieza>piezas_bla{}; // piezas del jugador blanco
	vector<Pieza>piezas_neg{}; // piezas del jugador negro

	Jugador turnoActual; //Variable para gestionar el turno actual en la partida 

public:
	Pieza* tablero[FILA][COLUMNA] = { nullptr }; /* Esto es como la interfaz.
	Tanto las funciones lógicas como las de dibujo accederán SÓLO a este dato.
	Con lo que hay en este dato basta para gestionar todo
	*/
  
	Tablero(); // constructor

	// operador para indexar con un vector
	inline Pieza* operator[](const Vector2D& posicion)const {
		return tablero[posicion.x][posicion.y];
	}


	/* La función de mover pieza está sobrecargada porque:
	* Puedes pasarle la pieza; si es externa, se volverá parte del tablero
	* Puedes pasarle la ubicación, ya que el tablero sabe qué pieza hay ahí
	*/

	/* Mueve una pieza de una casilla a otra y actualiza el turno */
	void mover_pieza(Vector2D p_ini, Vector2D p_fin);
	/*No uses esta. Usa la otra*/
	void mover_pieza(Pieza& _p, Vector2D p_fin);
	/* Activa el evento captura en una casilla determinada */
	void activar_captura(Vector2D _posicion);
	/* Activa el evento promoción en una casilla determinada */
	void activar_promocion(Vector2D _posicion, Tipo nuevo_tipo);
	/* Retorna la posición de uno de los reyes */
	Vector2D get_rey(Jugador _jugador);


	// Funciones para alterar manualmente el tablero
	/* Estas funciones en su mayoría son para hacer pruebas
	* NO SE USAN durante la partida.
	*/
	/* Vacía el tablero y borra las piezas */
	void vaciar();
	/* Para crear una pieza cualquiera en una casilla cualquiera */
	void crear_pieza(Tipo _tipo, Jugador _jugador, Vector2D _posicion);
	/* Devuelven una copia de los datos privados de la clase.
	* Las uso para comprobar si todos los datos se actualizan correctamente
	*/
	inline auto get_piezas_bla()const { return piezas_bla; }
	inline auto get_piezas_neg()const { return piezas_neg; }
	// FUNCIÓN PARA IMPRIMIR EL TABLERO POR LA CONSOLA
	void dibujar();
	// Función para que aparezca en la consola una lista de las piezas que hay en el tablero.
	// Usar esta función para verificar que las piezas y sus coordenadas se actualizan correctamente
	void mostrar_lista_de_piezas();
	// para consultar de quién es el turno
	inline auto get_turnoActual()const { return turnoActual; }

};