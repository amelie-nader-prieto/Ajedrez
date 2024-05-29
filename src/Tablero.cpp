#include "Tablero.h"

// constructor
Tablero::Tablero() :turnoActual(W) { //Inicializa el turno actual para que empiecen las blancas

	// Crea las piezas y las pone sobre el tablero

	// CREACI�N DE LAS PIEZAS
	// inicializa sus datos internos

	// Creaci�n de los peones
	for (int i = 2; i < COLUMNA - 2; i++) {
		piezas_neg.push_back(Pieza(Vector2D(2, i), B, P));
		piezas_bla.push_back(Pieza(Vector2D(7, i), W, P));
	} //Revisar las posiciones de las piezas, blancas van abajo y negras arriba

	// Creaci�n de las fichas en la fila intermedia
	// T C A C T
	vector<Tipo>tipos_fila_intermedia{ T,C,A,C,T };
	int j = 3;
	for (auto tipo : tipos_fila_intermedia) {
		piezas_neg.push_back(Pieza(Vector2D(1, j), B, tipo));
		piezas_bla.push_back(Pieza(Vector2D(8, j), W, tipo));

		j++;
	}

	// Creaci�n de las fichas en la fila del fondo
	// R A D
	vector<Tipo>tipos_fila_fondo{ R,A,D };
	j = 4;
	for (auto tipo : tipos_fila_fondo) {
		piezas_neg.push_back(Pieza(Vector2D(0, j), B, tipo));
		piezas_bla.push_back(Pieza(Vector2D(9, j), W, tipo));

		j++;

	}

	// filas 3 y 6: no hay nada
	j = 1;
	while (j < COLUMNA - 1) {
		tablero[3][j] = &ninguna;
		tablero[6][j] = &ninguna;
		j++;
	}

	// filas 4 y 5: no hay nada
	j = 0;
	while (j < COLUMNA) {
		tablero[4][j] = &ninguna;
		tablero[5][j] = &ninguna;
		j++;
	}

	// Una vez crea las piezas, inicializa la interfaz

	// inicializa la interfaz
	//REVISAR: se estan asignando direcciones de memoria de objetos locales
	//pn y pb a las posiciones del tablero, los objetos locales de destruir�n 
	//propuesta: almacenar copias de las piezas en el tablero  �C�mo?

	int indice = 0;
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			for (auto& pn : piezas_neg) {
				if (pn.GetPosicion().x == i && pn.GetPosicion().y == j)tablero[i][j] = &pn;
			}
			for (auto& pb : piezas_bla) {
				if (pb.GetPosicion().x == i && pb.GetPosicion().y == j)tablero[i][j] = &pb;
			}
		}
	}

}

void Tablero::mover_pieza(Vector2D p_ini, Vector2D p_fin) {
	//Termina la ejecuci�n del m�todo "mover_pieza" si se detecta que no es el jugador al que le toca
	//mover la pieza (al que le toca el turno). Impide que el movimiento de la pieza se realice
	if (tablero[p_ini.x][p_ini.y]->GetJugador() != turnoActual) {
		//No es el turno del Jugador que intenta mover la pieza
		std::cout << "No es tu turno!" << std::endl;
		return;
	}


	tablero[p_fin.x][p_fin.y] = tablero[p_ini.x][p_ini.y];
	tablero[p_ini.x][p_ini.y] = &ninguna; // la posici�n inicial se queda vac�a

	// busca la pieza que ha movido para actualizar sus coordenadas
	switch (tablero[p_fin.x][p_fin.y]->GetJugador()) {
	case B:
		for (auto p : piezas_neg) {
			if (p.GetPosicion() == p_ini)p.actualizar_coordenadas(p_fin);
		}
		break;

	case W:
		for (auto p : piezas_bla) {
			if (p.GetPosicion() == p_ini)p.actualizar_coordenadas(p_fin);
		}
		break;

	default:break;
	}

	//Cambia el turno al otro jugador: Despues de mover la pieza y actualizar las coordenadas
	//el turno se cambia al otro jugador, despues de cada movimiento v�lido el turno pasa al otro jugador
	turnoActual = (turnoActual == W) ? B : W;
}

void Tablero::activar_captura(Vector2D _posicion) {
	tablero[_posicion.x][_posicion.y]->set_captura();
	tablero[_posicion.x][_posicion.y] = &ninguna;
}


