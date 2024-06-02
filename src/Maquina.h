#pragma once
#include "LogicaAjedrez.h"

class Maquina
{
	Tablero& tablero;

	enum Estado { INICIO, AMENAZAS, NO_AMNZ, NO_AMNZ_POSIBLE_CAPTURA, CAPTURA, MOVER_RNDM, SI_AMNZ, SI_AMNZ_POSIBLE_CAPTURA, SI_AMNZ_NO_CAPTURA} estado = INICIO;

	vector<Pieza*>piezas_propias{}, piezas_rival{};

	bool fin_turno = false;
	
	struct amenaza
	{
		Pieza* pieza_amenazada;
		Pieza* pieza_atacante;
		int puntuacion; // atribuimo a cada amenaza una puntuación
	};

	struct captura
	{
		Pieza* pieza_atacante;
		Pieza* pieza_amenazada;
		int puntuacion; // atribuimos a cada captura una puntuacion
	};

	vector<amenaza>lista_amenazas{};
	vector<captura>lista_posibles_capturas{};

	bool puede_mover(Pieza* pieza, vector<Vector2D> posibles_mov);

	void obtener_amenazas();

	void obtener_capturas();
	
	void mover_rndm(Pieza* pieza);

	int puntuacion_captura(Pieza* pieza_atacada);

	static int puntuacion_pieza(Pieza* pieza)
	{
		// se atribuye a cada pieza un valor en función de su importancia
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

	bool comparar_amenazas(const amenaza& amnz1, const amenaza& amnz2); // condicion de ordenacion de lista de menazas

	bool comparar_capturas(const captura& cptr1, const captura& cptr2); // condicion de ordenación de lista de capturas

public:

	Maquina();

	void jugar(); // gestion de la máquina de estados
};


