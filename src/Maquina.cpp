#include "Maquina.h"
#include <algorithm>

using namespace std;


void Maquina::jugar() {
	bool amenazas = obtener_amenazas();
	bool capturas = obtener_capturas();
	switch (estado)
	{
	case Maquina::INICIO:
		// Inicio del turno
		if (!jaque_mate) estado = AMENAZAS;
		break;
	case Maquina::AMENAZAS:
		// Evaluar posibles amenazas
		if (amenazas) estado = SI_AMNZ;
		else estado = NO_AMNZ;
		break;
	case Maquina::NO_AMNZ:
		// Evaluar posibles capturas
		if (capturas) {
			capturar();
			estado = INICIO;
		}			
		else estado = MOVER_RND;
		break;
	case Maquina::SI_AMNZ:
		for (auto i : lista_amenazas)
			for (auto j : lista_posibles_capturas)
				if ((i.pieza_atacante == j.pieza_amenazada) && (j.puntuacion >= 0))
					capturar(); // capturar pieza atacante con la captura mas conveniente
				else mover_rndm(); // sino mover pieza amenazada
		estado = INICIO;
		break;
	case Maquina::MOVER_RND:
		// determinar pieza random así como un movimiento random de sus posibles movimeintos
		mover_rndm();
		estado = INICIO;
		break;
	default:
		break;
	}
}

bool Maquina::obtener_amenazas()
{
	amenaza amnz{};
	for (auto i : piezas_rival) {
		vector<Vector2D>posibles_mov = obtener_posibles_movimientos(*i, tablero); // obtener posibles movimientos de la pieza rival
		for (auto j : posibles_mov) {
			for (auto k : piezas_propias)
				if (k->GetPosicion() == j)
				{
					amnz = { k,i, puntuacion_pieza(k) - puntuacion_pieza(i) };
					lista_amenazas.push_back(amnz);
				}									
		}
	}
	if (lista_amenazas.empty()) return false;
	else {
		//ordenar amenazas de mayor a menor en funcion de su puntuacion
		sort(lista_amenazas.begin(), lista_amenazas.end(), comparar_amenazas);
		return true;
	}
}

bool Maquina::obtener_capturas()
{
	captura cptr{};
	for (auto i : piezas_propias) {
		vector<Vector2D>posibles_mov = obtener_posibles_movimientos(*i, tablero); // obtener posibles movimientos de la pieza rival
		for (auto j : posibles_mov) {
			for (auto k : piezas_rival)
				if (k->GetPosicion() == j)
				{
					cptr = { i,k, puntuacion_pieza(k) - puntuacion_pieza(i) };
					lista_posibles_capturas.push_back(cptr);
				}					
		}
	}
	if (lista_posibles_capturas.empty()) return false;
	else {
		sort(lista_posibles_capturas.begin(), lista_posibles_capturas.end(), comparar_capturas);
		return true;
	}
}

int Maquina::puntuacion_pieza(Pieza* pieza) 
{
	// se atribuye a cada pieza un valor en función de su importancia
	switch (pieza->GetTipo())
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

bool Maquina::comparar_amenazas(const amenaza& amnz1, const amenaza& amnz2)
{
	return amnz1.puntuacion > amnz2.puntuacion;
}

bool Maquina::comparar_capturas(const captura& cptr1, const captura& cptr2)
{
	return cptr1.puntuacion > cptr2.puntuacion;
}