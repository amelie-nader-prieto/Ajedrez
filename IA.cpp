#include "IA.h"

using namespace std;

void IA::jugar(Tablero& tab) {
	piezas_propias.clear();
	piezas_rival.clear();
	lista_amenazas.clear();
	lista_posibles_capturas.clear();
	// Igualo los vectores de la IA, piezas_propias y piezas_rival, a los vectores del tablero según la variable jugador
	inicializar(tab, jugador);
	/*jugador == W ?
		piezas_propias = tab.piezas_bla, piezas_rival = tab.piezas_neg :
		piezas_propias = tab.piezas_neg, piezas_rival = tab.piezas_bla;*/
	// Analiza la situación del tablero que le has pasado, para saber:
	// - cuáles que sus piezas están en peligro
	// - qué piezas rivales podría capturas
	obtener_amenazas(tab);
	obtener_capturas(tab);
	bool hay_amenazas = lista_amenazas.size();
	bool puede_capturar = lista_posibles_capturas.size();
	vector<Vector2D> posibles_mov{};
	fin_turno = false;
	// Utiliza la máquina de estado para tomar una decisión (realizar una jugada)
	while (!fin_turno) {
		switch (estado)
		{
		case IA::INICIO:
			cout << "INICIO" << endl;
			// Inicio del turno
			if (fin_turno) 
				break;
			else 
				estado = AMENAZAS;
			break;
		case IA::AMENAZAS:
			// Evaluación de amenazas
			cout << "AMENAZAS" << endl;
			if (hay_amenazas) 
				// Si hay amenazas voy a...
				estado = SI_AMNZ;
			else 
				// Si no hay amenazas voy a...
				estado = NO_AMNZ;
			break;
		case IA::NO_AMNZ:
			// No hay amenazas. Evaluaión de capturas
			cout << "NO_AMNZ" << endl;
			// Evaluar si se puede capturar o no
			if (puede_capturar)	
				// Si puede capturar voy a...
				estado = NO_AMNZ_POSIBLE_CAPTURA;
			else 
				// Si no puede capturar voy a...
				estado = MOVER_RNDM;
			break;
		case IA::NO_AMNZ_POSIBLE_CAPTURA:
			// No hay amenazas. Evaluación de posibles capturas
			cout << "NO_AMNZ_POSIBLE_CAPTURA" << endl;
			// evalua la captura mas conveniente, si no compensa mueve
			if (puede_capturar) {
				// Si puede capturar, captura
				estado = CAPTURA;
				break;
			}
			else 
				// Si no puede capturar voy a...
				estado = MOVER_RNDM;
			break;
		case IA::CAPTURA:
			// Realiza la captura con mayor puntuación, la que corresponde a la cpatura de la pieza mas importante del rival entre las posibles capturas
			cout << "CAPTURA" << endl;
			mover_pieza(lista_posibles_capturas.back().pieza_atacante.GetPosicion(), lista_posibles_capturas.back().pieza_amenazada.GetPosicion(), tab);
			fin_turno = true; // Fin del tunro vuelve a inicio
			estado = INICIO;
			break;
		case IA::MOVER_RNDM:
			// MOVIMIENTO RANDOM
			// determinar pieza random así como un movimiento random de sus posibles movimeintos
			cout << "MOVER_RNDM" << endl;
			mover_rndm(tab);
			fin_turno = true; // Fin del turno, vuelve a INICIO
			estado = INICIO;
			break;
		case IA::SI_AMNZ:
			// Si hay amenazas. Evalua si puede capturar o no
			cout << "SI_AMNZ" << endl;
			if (puede_capturar)
				// Si hay capturas posibles voy a...
				estado = SI_AMNZ_POSIBLE_CAPTURA;
			else
				// Si no hay capturas posibles voy a...
				estado = SI_AMNZ_NO_CAPTURA;
			break;
		case IA::SI_AMNZ_POSIBLE_CAPTURA:
			// Si hay amenazas y posibles capturas
			cout << "SI_AMNZ_POSIBLE_CAPTURA" << endl;
			// evalua si la captura con mayor puntuacion es superior a la amenaza con mayor puntuacion
			if (lista_amenazas.back().puntuacion > lista_posibles_capturas.back().puntuacion)
				// Si tiene mayor puntuación la amenaza, no captura, voy a...
				estado = SI_AMNZ_NO_CAPTURA;
			else 
				// Si tiene mayor puntuación la captura, captura, voy a...
				estado = CAPTURA;
			break;
		case IA::SI_AMNZ_NO_CAPTURA:
			// Hay amenazas y no hay capturas posibles
			cout << "SI_AMNZ_NO_CAPTURA" << endl;
			if (puede_mover(lista_amenazas.back().pieza_amenazada, posibles_mov, tab)) {
				//Si puede mover la pieza amenazada mueve la pieza amenazada de mayor puntuación
				// de forma aleatoria dentro de sus posibles movimientos
				mover_pieza(lista_amenazas.back().pieza_amenazada.GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tab);
				fin_turno = true; // Fin del turno
				estado = INICIO;
			}
			else {
				// Si la pieza amenazada no se puede mover la elimino de la lista de amenazas y vuelvo a analizar
				// las posibles amenazas. Voy a ...
				lista_amenazas.pop_back();
				estado = AMENAZAS;
			}
			break;
		default:
			break;
		}
	}
}

void IA::inicializar(Tablero& tab, Jugador J) {
	for (auto& i : this->jugador == W ? tab.get_piezas_bla() : tab.get_piezas_neg())
		piezas_propias.push_back(i);
	for (auto& i : this->jugador == W ? tab.get_piezas_neg() : tab.get_piezas_bla())
		piezas_rival.push_back(i);
}

void IA::mover_rndm(Tablero& tab) {
	Pieza pieza;
	vector<Vector2D>posibles_mov{};
	while (posibles_mov.size() == 0){
		pieza = piezas_propias[GetRandom(piezas_propias.size())];
		posibles_mov = obtener_movimientos_legales(pieza.GetPosicion(), tab);
	}
	mover_pieza(pieza.GetPosicion(), posibles_mov[GetRandom(posibles_mov.size())], tab);
}

bool IA::puede_mover(Pieza& pieza, vector<Vector2D>& posibles_mov, Tablero& tab) {
	posibles_mov = obtener_movimientos_legales(pieza.GetPosicion(), tab);
	return posibles_mov.size();
}

void IA::obtener_amenazas(Tablero tab) {
	evento amnz{};
	for (auto& i : piezas_rival) {
		// obtener posibles movimientos de cada pieza rival
		vector<Vector2D>posibles_mov_rival = obtener_movimientos_legales(i.GetPosicion(), tab);
		if(posibles_mov_rival.size() != 0) // si la pieza dada tiene movimeitnos posibles
			for (auto j : posibles_mov_rival) {
				// Para cada posible movimiento de la pieza rival...
				for (auto& k : piezas_propias)
					if (k.GetPosicion() == j) { // Si coincide con la posición de alguna de tus piezas, dicha pieza está amenazada
						cout << "Hay amenaza" << endl;
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
	for (auto& i : piezas_propias) {
		// obtener posibles movimientos de cada una de las piezas propias
		vector<Vector2D>posibles_mov = obtener_movimientos_legales(i.GetPosicion(), tab);
		if(posibles_mov.size() != 0) // si la pieza dad tiene posibles movimientos
			for (auto j : posibles_mov) {
				// Para cada posible movimientos de la pieza...
				for (auto& k : piezas_rival)
					if (k.GetPosicion() == j) { // Si coincide con la posición de una pieza rival, dicha pieza puede capturar
						cout << "Hay caputra" << endl;
						cptr = { k,i, puntuacion_pieza(k) };
						lista_posibles_capturas.push_back(cptr); // lo añade a la lista de posibles capturas
					}
			}		
	}
	ordenar_eventos(lista_posibles_capturas); // ordena las posibles capturas en función de su puntuación
}

void IA::ordenar_eventos(vector<evento>& lista) {
	// ordena los evento en función de su puntuación de forma decreciente
	for (int i = 1; i < lista.size(); i++) {
		for (int j = 0; i < lista.size() - 1; j++) {
			if (lista[j].puntuacion > lista[j + 1].puntuacion) {
				evento aux = lista[j + 1];
				lista[j + 1] = lista[j];
				lista[j] = aux;
			}
		}
	}
}




