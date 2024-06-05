#include "IA.h"

using namespace std;

bool IA::jugar(Tablero&tab) {
	// Inicializa sus piezas y las del rival
	piezas_propias = (jugador == B ? tab.get_piezas_neg() : tab.get_piezas_bla());
	piezas_rival = (jugador == B ? tab.get_piezas_bla() : tab.get_piezas_neg());

	// Analiza la situación del tablero que le has pasado, para saber:
	// - cuáles que sus piezas están en peligro
	// - qué piezas rivales podría capturas
	obtener_amenazas(tab);
	obtener_capturas(tab);
	bool hay_amenazas = lista_amenazas.size();
	bool puede_capturar = lista_posibles_capturas.size();

	fin_turno = false;
	// Utiliza la máquina de estado para tomar una decisión (realizar una jugada)
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
			mover_pieza(lista_posibles_capturas[0].pieza_atacante.GetPosicion(), lista_posibles_capturas[0].pieza_amenazada.GetPosicion(), tab);
			fin_turno = true;
			estado = INICIO;
			break;
		case IA::MOVER_RNDM:
			// MOVIMIENTO RANDOM
			// determinar pieza random así como un movimiento random de sus posibles movimeintos
			// no se evalua la posibilidad de que no se pueda mover ninguna pieza. De eso se encarga la lógica
			while (!fin_turno) {
				vector<Vector2D>posibles_mov;
				Pieza pieza = piezas_propias[GetRandom(piezas_propias.size())];
				// si se puede mover, mover aleatoriamente y salir del bucle
				if (puede_mover(pieza, posibles_mov, tab)) {
					mover_pieza(pieza.GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tab);
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
			mover_rndm(lista_amenazas[0].pieza_amenazada,tab);
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

void IA::mover_rndm(Pieza pieza, Tablero tab) {
	vector<Vector2D>posibles_mov;
	if (puede_mover(pieza, posibles_mov, tab)) {
		mover_pieza(pieza.GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tab);
		fin_turno = true;
	}
}

void IA::obtener_amenazas(Tablero tab) {
	evento amnz{};

	// Inicializa tus piezas propias y las del rival a partir del tablero que se ha pasado por argumento
	/*piezas_propias = (jugador == B ? tab.get_piezas_neg() : tab.get_piezas_bla());
	piezas_rival = (jugador == B ? tab.get_piezas_bla() : tab.get_piezas_neg());
	*/
	for (auto i : piezas_rival) {
		// obtener posibles movimientos de cada pieza rival
		vector<Vector2D>posibles_mov_rival = obtener_posibles_movimientos(i.GetPosicion(), tab);
		for (auto j : posibles_mov_rival) {
			// Para cada posible movimiento de la pieza rival...
			for (auto k : piezas_propias)
				if (k.GetPosicion() == j) { // Si coincide con la posición de alguna de tus piezas, dicha pieza está amenazada
					amnz = { k,i,puntuacion_pieza(k) };
					lista_amenazas.push_back(amnz); // lo añade a la lista de amenazas
				}
		}
	}

	//ordenar amenazas de mayor a menor en funcion de su puntuacion
	ordenar_eventos(lista_amenazas);
}

void IA::obtener_capturas(Tablero tab) {
	evento cptr{};

	/*piezas_propias = (jugador == B ? tab.get_piezas_neg() : tab.get_piezas_bla());
	piezas_rival = (jugador == B ? tab.get_piezas_bla() : tab.get_piezas_neg());*/

	for (auto i : piezas_propias) {
		// obtener posibles movimientos de la pieza rival
		vector<Vector2D>posibles_mov = obtener_posibles_movimientos(i.GetPosicion(), tab);
		for (auto j : posibles_mov) {
			for (auto k : piezas_rival)
				if (k.GetPosicion() == j) {
					cptr = { i,k, puntuacion_pieza(k) };
					lista_posibles_capturas.push_back(cptr);
				}
		}
	}
	ordenar_eventos(lista_posibles_capturas); // ordena las posibles capturas en función de su puntuación
}

bool IA::puede_mover(Pieza pieza, vector<Vector2D> posibles_mov, Tablero& tab)
{
	posibles_mov = obtener_posibles_movimientos(pieza.GetPosicion(), tab);
	if (posibles_mov.size() == 0) return false;
	else return true;
}

void IA::ordenar_eventos(vector<evento> lista) {
	// ordena los evento en función de su puntuación de forma decreciente
	for (int i = 1; i < lista.size(); i++) {
		for (int j = 0; i < lista.size() - 1; j++) {
			if (lista[j].puntuacion < lista[j+1].puntuacion) {
				evento aux = lista[j + 1];
				lista[j + 1] = lista[j];
				lista[j] = aux;
			}
		}
	}
}