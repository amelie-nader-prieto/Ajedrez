#pragma once
#include "LogicaAjedrez.h"

class IA
{
	//Tablero& tablero; 
	Tablero tablero; // representa el tablero en el que está transcurriendo la partida

	// Estados de la máquina
	/*
	* INICIO: Inicio del turno
	* AMENAZAS: Evaluando posibles amenazas
	* SI_AMNZ: Se han encontrado piezas amenazadas
	* NO_AMNZ: No tienes ninguna pieza amenazada
	* NO_AMN_POSIBLE_CAPTURA: No tienes piezas amenazadas, y puedes realizar alguna captura
	* CAPTURA: Evaluando la captura más conveniente
	* MOVER_RNDM: Seleccionando una pieza para realizar un movimiento al azar
	* SI_AMNZ_POSIBLE_CAPTURA: Tienes piezas amenazadas y puedes capturar - evaluará la opción más conveniente
	* SI_AMNZ_NO_CAPTURA: Tienes piezas amenazadas y no puedes capturar (supongo)
	*/
	enum Estado { INICIO, AMENAZAS, NO_AMNZ, NO_AMNZ_POSIBLE_CAPTURA, CAPTURA, MOVER_RNDM, SI_AMNZ, SI_AMNZ_POSIBLE_CAPTURA, SI_AMNZ_NO_CAPTURA} estado = INICIO;

	Jugador jugador; // la IA jugará con las piezas blancas o negras
	vector<Pieza*>piezas_propias{}, piezas_rival{};

	bool fin_turno = false; // esta variable se usa para gestionar el final del turno
	
	struct amenaza
	{
		Pieza* pieza_amenazada; // Pieza tuya que podría ser capturada en el turno siguiente
		Pieza* pieza_atacante; // Pieza del rival que podría capturarla
		int puntuacion; // atribuimos a cada amenaza una puntuación
	};
	struct captura
	{
		Pieza* pieza_atacante; // Pieza tuya que puede realizar una captura en el turno siguiente
		Pieza* pieza_amenazada; // Pieza del rival a la que puedes capturar
		int puntuacion; // atribuimos a cada captura una puntuacion
	};

	vector<amenaza>lista_amenazas{};
	vector<captura>lista_posibles_capturas{};

	/* Para saber si una pieza puede moverse */
	bool puede_mover(Pieza* pieza, vector<Vector2D> posibles_mov);
	// obtiene las amenazas posibles y las ordena por su puntuacion
	void obtener_amenazas();
	void obtener_amenazas(Tablero tab);
	// obtiene las capturas posibles y las ordena por puntuacion
	void obtener_capturas();
	void obtener_capturas(Tablero tab);
	/* Mueve una pieza (pasada como argumento) a una casilla al azar */
	void mover_rndm(Pieza* pieza);
	/* Esta sobrecarga hace lo mismo pero con un tablero externo */
	void mover_rndm(Pieza* pieza, Tablero tab);
	/*
	* Para obtener la puntuación de una captura
	* Evalúa una captura en función de la puntuación de las piezas que intervienen y de si
	* la pieza atacada en la captura interviene en una amenaza
	*/
	int puntuacion_captura(Pieza* pieza_atacada);
	// se atribuye a cada pieza un valor en función de su importancia
	static int puntuacion_pieza(Pieza* pieza)
	{
		
		switch (pieza->GetTipo())
		{
		case R:
			return 100;
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
	/*
	* Compara 2 amenazas
	TRUE si la primera es de mayor puntuación que la segunda, false si no
	*/
	bool comparar_amenazas(const amenaza& amnz1, const amenaza& amnz2); // condicion de ordenacion de lista de menazas
	/*
	* Compara 2 capturas
	* TRUE si la primera es de mayor puntuación que la segunda, false si no
	*/
	bool comparar_capturas(const captura& cptr1, const captura& cptr2); // condicion de ordenación de lista de capturas

public:
	// constructor por defecto
	IA(Jugador _jugador=W) :jugador(_jugador) {}

	/*
	* Para realizar una jugada completa
	Revisa todo el tablero, toma una decisión y mueve una pieza
	*/
	void jugar(); // gestion de la máquina de estados
	/*Esta sobrecarga recibe un tablero externo como argumento y
	retorna la variable fin_turno (así, indica al objeto que llamó a la función
	que el turno se ha realizado con éxito) */
	bool jugar(Tablero&tab);

};


