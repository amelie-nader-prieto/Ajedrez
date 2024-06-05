#include "IA.h"
#include <algorithm>

using namespace std;



void IA::jugar(){
	// iniciar las varibales de lista de piezas
	obtener_amenazas();
	obtener_capturas();
	bool hay_amenazas = lista_amenazas.size();
	bool puede_capturar = lista_posibles_capturas.size();
	fin_turno = false;
	while (!fin_turno)
	{
		switch (estado)
		{
		case IA::INICIO:
			// Inicio del turno
			if (fin_turno) break;
			estado = AMENAZAS;
			break;
		case IA::AMENAZAS:
			// Evaluar posibles amenazas
			if (hay_amenazas) estado = SI_AMNZ;
			else estado = NO_AMNZ;
			break;
		case IA::NO_AMNZ:
			// Evaluar si se puede capturar o no
			if (puede_capturar)
				estado = NO_AMNZ_POSIBLE_CAPTURA;
			else estado = MOVER_RNDM;
			break;
		case IA::NO_AMNZ_POSIBLE_CAPTURA:
			// evalua la captura mas conveniente, si no compensa mueve
			if (puede_capturar) {
				// CAPTURA SIEMPRE QUE PUEDA
				// HAY QUE EVALUAR OTROS EVENTOS
				estado = CAPTURA;
				break;
			}
			else estado = MOVER_RNDM;
			break;
		case IA::CAPTURA:
			// realiza la captura más conveniente
			mover_pieza(lista_posibles_capturas[0].pieza_atacante->GetPosicion(), lista_posibles_capturas[0].pieza_amenazada->GetPosicion(), tablero);
			fin_turno = true;
			estado = INICIO;
			break;
		case IA::MOVER_RNDM:
			// MOVIMIENTO RANDOM
			// determinar pieza random así como un movimiento random de sus posibles movimeintos
			// no se evalua la posibilidad de que no se pueda mover ninguna pieza. De eso se encarga la lógica
			while (!fin_turno) {
				vector<Vector2D>posibles_mov;
				Pieza* pieza = piezas_propias[GetRandom(piezas_propias.size())];
				// si se puede mover, mover aleatoriamente y salir del bucle
				if (puede_mover(pieza, posibles_mov)) {
					mover_pieza(pieza->GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tablero);
					fin_turno = true;
				}
			}
			estado = INICIO;
			break;
		case IA::SI_AMNZ:
			if (puede_capturar)
				estado = SI_AMNZ_POSIBLE_CAPTURA;
			else
				estado = SI_AMNZ_NO_CAPTURA;
			break;
		case IA::SI_AMNZ_POSIBLE_CAPTURA:
			// evalua si la captura con mayor puntuacion es superior a la amenaza con mayor puntuacion
			if (lista_amenazas[0].puntuacion > lista_posibles_capturas[0].puntuacion)
				estado = SI_AMNZ_NO_CAPTURA;
			else estado = CAPTURA;
			break;
			/*for (auto& i : lista_amenazas) {
				for (auto j : lista_posibles_capturas) {
					if ((i.pieza_atacante == j.pieza_amenazada) && (j.puntuacion >= 0)) {
						// capturar pieza atacante con la captura mas conveniente
						mover_pieza(j.pieza_atacante->GetPosicion(), j.pieza_amenazada->GetPosicion(), tablero);
						fin_turno = true;
						break;
					}
				}
				if (!fin_turno) { // no puedo comer pieza atacante
					vector<Vector2D>posibles_mov;
					// si se puede mover, mover aleatoriamente
					if (puede_mover(i.pieza_amenazada, posibles_mov)) {
						mover_pieza(i.pieza_amenazada->GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tablero);
						fin_turno = true;
						break;
					}
					// si no puedo mover la pieza amenazada pasar a la siguinete amenaza
					else {
						continue;
					}
				}
				// salir del bucle en cuanto haya movido o capturado
				if (fin_turno) {
					estado = INICIO;
					break;
				}
			}
			// si no puedo mover ninguna pieza amenazada ni capturar a la pieza atacante ir a NO_AMNZ
			if (!fin_turno)
				estado = NO_AMNZ;
			break;
			*/
		case IA::SI_AMNZ_NO_CAPTURA:
			mover_rndm(lista_amenazas[0].pieza_amenazada);
			if (fin_turno)
				// si se ha podido mover la pieza amenazada
				estado = INICIO;
			else {
				// si la pieza amenazada no se ha podeido mover la elimino de la lista de amenazas y vuelvo a evaluar amenazas
				lista_amenazas.erase(lista_amenazas.begin());
				hay_amenazas = lista_amenazas.size();
				estado = AMENAZAS;
			}
			break;
		default:
			break;
		}
	}
}
bool IA::jugar(Tablero&tab) {

	tablero = tab;

	obtener_amenazas();
	obtener_capturas();
	bool hay_amenazas = lista_amenazas.size();
	bool puede_capturar = lista_posibles_capturas.size();
	fin_turno = false;
	while (!fin_turno)
	{
		switch (estado)
		{
		case IA::INICIO:
			// Inicio del turno
			if (fin_turno) break;
			estado = AMENAZAS;
			break;
		case IA::AMENAZAS:
			// Evaluar posibles amenazas
			if (hay_amenazas) estado = SI_AMNZ;
			else estado = NO_AMNZ;
			break;
		case IA::NO_AMNZ:
			// Evaluar si se puede capturar o no
			if (puede_capturar)
				estado = NO_AMNZ_POSIBLE_CAPTURA;
			else estado = MOVER_RNDM;
			break;
		case IA::NO_AMNZ_POSIBLE_CAPTURA:
			// evalua la captura mas conveniente, si no compensa mueve
			if (puede_capturar) {
				// CAPTURA SIEMPRE QUE PUEDA
				// HAY QUE EVALUAR OTROS EVENTOS
				estado = CAPTURA;
				break;
			}
			else estado = MOVER_RNDM;
			break;
		case IA::CAPTURA:
			// realiza la captura más conveniente
			mover_pieza(lista_posibles_capturas[0].pieza_atacante->GetPosicion(), lista_posibles_capturas[0].pieza_amenazada->GetPosicion(), tablero);
			fin_turno = true;
			estado = INICIO;
			break;
		case IA::MOVER_RNDM:
			// MOVIMIENTO RANDOM
			// determinar pieza random así como un movimiento random de sus posibles movimeintos
			// no se evalua la posibilidad de que no se pueda mover ninguna pieza. De eso se encarga la lógica
			while (!fin_turno) {
				vector<Vector2D>posibles_mov;
				Pieza* pieza = piezas_propias[GetRandom(piezas_propias.size())];
				// si se puede mover, mover aleatoriamente y salir del bucle
				if (puede_mover(pieza, posibles_mov)) {
					mover_pieza(pieza->GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tablero);
					fin_turno = true;
				}
			}
			estado = INICIO;
			break;
		case IA::SI_AMNZ:
			if (puede_capturar)
				estado = SI_AMNZ_POSIBLE_CAPTURA;
			else
				estado = SI_AMNZ_NO_CAPTURA;
			break;
		case IA::SI_AMNZ_POSIBLE_CAPTURA:
			// evalua si la captura con mayor puntuacion es superior a la amenaza con mayor puntuacion
			if (lista_amenazas[0].puntuacion > lista_posibles_capturas[0].puntuacion)
				estado = SI_AMNZ_NO_CAPTURA;
			else estado = CAPTURA;
			break;
		case IA::SI_AMNZ_NO_CAPTURA:
			mover_rndm(lista_amenazas[0].pieza_amenazada);
			if (fin_turno)
				// si se ha podido mover la pieza amenazada
				estado = INICIO;
			else {
				// si la pieza amenazada no se ha podeido mover la elimino de la lista de amenazas y vuelvo a evaluar amenazas
				lista_amenazas.erase(lista_amenazas.begin());
				hay_amenazas = lista_amenazas.size();
				estado = AMENAZAS;
			}
			break;
		default:
			break;
		}
	}
	return fin_turno;
}


void IA::mover_rndm(Pieza* pieza) {
	vector<Vector2D> posibles_mov;
	if (puede_mover(pieza, posibles_mov)) {
		mover_pieza(pieza->GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tablero);
		fin_turno = true;
	}
}

void IA::obtener_amenazas() {
	// obtiene las amenazas posibles y las ordena por su puntuacion
	amenaza amnz{};
	for (auto i : piezas_rival) {
		vector<Vector2D>posibles_mov = obtener_posibles_movimientos(*i, tablero); // obtener posibles movimientos de la pieza rival
		for (auto j : posibles_mov) {
			for (auto k : piezas_propias)
				if (k->GetPosicion() == j) {
					amnz = { k,i,puntuacion_pieza(k)};
					lista_amenazas.push_back(amnz);
				}									
		}
	}
	//ordenar amenazas de mayor a menor en funcion de su puntuacion
	sort(lista_amenazas.begin(), lista_amenazas.end(), [](int a, int b) {return a > b; });
}

void IA::obtener_capturas() {
	// obtiene las capturas posibles y las ordena por puntuacion
	captura cptr{};
	for (auto i : piezas_propias) {
		vector<Vector2D>posibles_mov = obtener_posibles_movimientos(*i, tablero); // obtener posibles movimientos de la pieza rival
		for (auto j : posibles_mov) {
			for (auto k : piezas_rival)
				if (k->GetPosicion() == j) {
					cptr = { i,k, puntuacion_pieza(k) };
					lista_posibles_capturas.push_back(cptr);
				}					
		}
	}
	sort(lista_posibles_capturas.begin(), lista_posibles_capturas.end(), comparar_capturas);
}

int IA::puntuacion_captura(Pieza* pieza_atacada) {
	// Evalua una captura en funcion de la puntuacion de las piezas que intervienen y si la pieza atacada en la captura interviene en una amenaza
	int puntuacion_cptr = puntuacion_pieza(pieza_atacada); 
	for (auto& i : lista_amenazas)
		if (i.pieza_atacante == pieza_atacada) {
			puntuacion_cptr += i.puntuacion;
		}
	return puntuacion_cptr;			
}

bool IA::puede_mover(Pieza* pieza, vector<Vector2D> posibles_mov)
{
	posibles_mov = obtener_posibles_movimientos(*pieza, tablero);
	if (posibles_mov.size() == 0) return false;
	else return true;
}

bool IA::comparar_amenazas(const amenaza& amnz1, const amenaza& amnz2)
{
	return amnz1.puntuacion > amnz2.puntuacion;
}

bool IA::comparar_capturas(const captura& cptr1, const captura& cptr2)
{
	return cptr1.puntuacion > cptr2.puntuacion;
}

static int GetRandom(int max)
{
	// Usa la hora actual como semilla para el generador de números aleatorios
	srand(time(0));
	return (rand() % max);
}