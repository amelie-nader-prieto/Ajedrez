#pragma once
#include "LogicaAjedrez.h"

class IA
{
	//Tablero& tablero; 
	Tablero tablero; // representa el tablero en el que est� transcurriendo la partida

	// Estados de la m�quina
	/*
	* INICIO: Inicio del turno
	* AMENAZAS: Evaluando posibles amenazas
	* SI_AMNZ: Se han encontrado piezas amenazadas
	* NO_AMNZ: No tienes ninguna pieza amenazada
	* NO_AMN_POSIBLE_CAPTURA: No tienes piezas amenazadas, y puedes realizar alguna captura
	* CAPTURA: Evaluando la captura m�s conveniente
	* MOVER_RNDM: Seleccionando una pieza para realizar un movimiento al azar
	* SI_AMNZ_POSIBLE_CAPTURA: Tienes piezas amenazadas y puedes capturar - evaluar� la opci�n m�s conveniente
	* SI_AMNZ_NO_CAPTURA: Tienes piezas amenazadas y no puedes capturar (supongo)
	*/
	enum Estado { INICIO, AMENAZAS, NO_AMNZ, NO_AMNZ_POSIBLE_CAPTURA, CAPTURA, MOVER_RNDM, SI_AMNZ, SI_AMNZ_POSIBLE_CAPTURA, SI_AMNZ_NO_CAPTURA} estado = INICIO;

	Jugador jugador; // la IA jugar� con las piezas blancas o negras
	vector<Pieza>piezas_propias{}, piezas_rival{};

	bool fin_turno = false; // esta variable se usa para gestionar el final del turno
	
	struct evento // Un evento puede ser una captura o una amenaza
	{
		Pieza pieza_amenazada; // Pieza amenazada en el evento, puede ser propia o del rival
		Pieza pieza_atacante; // Pieza atacante en el evento, puede ser propia o del rival
		int puntuacion; // atribuimos a cada amenaza una puntuaci�n
	};

	vector<evento>lista_amenazas{};
	vector<evento>lista_posibles_capturas{};

	/* Para saber si una pieza puede moverse */
	bool puede_mover(Pieza pieza, vector<Vector2D> posibles_mov);
	void ordenar_eventos(vector<evento> lista);
	// obtiene las amenazas posibles y las ordena por su puntuacion
	void obtener_amenazas();
	void obtener_amenazas(Tablero tab);
	// obtiene las capturas posibles y las ordena por puntuacion
	void obtener_capturas();
	void obtener_capturas(Tablero tab);
	/* Mueve una pieza (pasada como argumento) a una casilla al azar */
	void mover_rndm(Pieza pieza);
	/* Esta sobrecarga hace lo mismo pero con un tablero externo */
	void mover_rndm(Pieza pieza, Tablero tab);
	/*
	* Para obtener la puntuaci�n de una captura
	* Eval�a una captura en funci�n de la puntuaci�n de las piezas que intervienen y de si
	* la pieza atacada en la captura interviene en una amenaza
	*/

	static int puntuacion_pieza(Pieza pieza)
	{
		
		switch (pieza.GetTipo())
		{
		case R:
			return 10;
			break;
		case D:
			return 9;
			break;
		case C:
			return 3;
			break;
		case A:
			return 3;
			break;
		case T:
			return 5;
			break;
		case P:
			return 1;
			break;
		default:
			return 0;
			break;
		}
	}

public:

	/*
	* Para realizar una jugada completa
	Revisa todo el tablero, toma una decisi�n y mueve una pieza
	*/
	void jugar(); // gestion de la m�quina de estados
	/*Esta sobrecarga recibe un tablero externo como argumento y
	retorna la variable fin_turno (as�, indica al objeto que llam� a la funci�n
	que el turno se ha realizado con �xito) */
	bool jugar(Tablero&tab);

};

static int GetRandom(int max)
{
	// Usa la hora actual como semilla para el generador de n�meros aleatorios
	srand(time(0));
	return (rand() % max);
}


