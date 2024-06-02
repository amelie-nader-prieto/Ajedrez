#pragma once
#include "LogicaAjedrez.h"

class Maquina
{
	Tablero& tablero;

	enum Estado { INICIO, AMENAZAS, NO_AMNZ, SI_AMNZ, MOVER_RND} estado = INICIO;

	vector<Pieza*>piezas_propias{}, piezas_rival{};

	bool fin_turno = false;
	
	struct amenaza
	{
		Pieza* pieza_amenazada;
		Pieza* pieza_atacante;
		int puntuacion; // atribuimo a cada amenaza una puntuaci�n
	};

	struct captura
	{
		Pieza* pieza_atacante;
		Pieza* pieza_amenazada;
		int puntuacion; // atribuimos a cada captura una puntuacion
	};

	vector<amenaza>lista_amenazas{};
	vector<captura>lista_posibles_capturas{};

	void capturar(); // capturar pieza una vez decidido que se hace

	bool obtener_amenazas();

	bool puede_mover(Pieza* pieza, vector<Vector2D> posibles_mov);

	bool obtener_capturas();

	int puntuacion_pieza(Pieza*);

	bool comparar_amenazas(const amenaza& amnz1, const amenaza& amnz2); // condicion de ordenacion de lista de menazas

	bool comparar_capturas(const captura& cptr1, const captura& cptr2); // condicion de ordenaci�n de lista de capturas

public:

	Maquina();

	void jugar(); // gestion de la m�quina de estados
};


