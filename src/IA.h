#pragma once
#include "LogicaAjedrez.h"


class IA
{
	vector<Pieza> piezas_propias{}, piezas_rival{};

	bool fin_turno = false;	

	bool puede_mover(Pieza& pieza, vector<Vector2D> &posibles_mov, Tablero& tab);

public:

	/* Mueve una pieza aleatoria de forma aleatoria entre de sus movimientos posbles*/
	void mover_rndm(Tablero& tab);

	void inicializar(Tablero& tab); // incializa la IA con las piezas propias las del rival y el tablero

};

static int GetRandom(int max)
{
	// Usa la hora actual como semilla para el generador de números aleatorios
	srand(time(0));
	return (rand() % max);
}
