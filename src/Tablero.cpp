#include "Tablero.h"

// constructor
Tablero::Tablero() {

	// Crea las piezas y las pone sobre el tablero

	// CREACIÓN DE LAS PIEZAS
	// inicializa sus datos internos

	// Creación de los peones
	for (int i = 2; i < COLUMNA - 2; i++) {
		piezas_neg.push_back(Pieza(Vector2D(2, i), B, P));
		piezas_bla.push_back(Pieza(Vector2D(7, i), W, P));
	}

	// Creación de las fichas en la fila intermedia
	// T C A C T
	vector<Tipo>tipos_fila_intermedia{ T,C,A,C,T };
	int j = 3;
	for (auto tipo : tipos_fila_intermedia) {
		piezas_neg.push_back(Pieza(Vector2D(1, j), B, tipo));
		piezas_bla.push_back(Pieza(Vector2D(8, j), W, tipo));

		j++;
	}

	// Creación de las fichas en la fila del fondo
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

/* La función de mover pieza está sobrecargada porque:
* Puedes pasarle la pieza; si es externa, se volverá parte del tablero
* Puedes pasarle la ubicación, ya que el tablero sabe qué pieza hay ahí
*/
void Tablero::mover_pieza(Vector2D p_ini, Vector2D p_fin) {
	// se asegura de que no intentes mover una pieza que no existe
	if (
		(!tablero[p_ini.x][p_ini.y]) || (tablero[p_ini.x][p_ini.y]->GetTipo() == no_hay)
		)return void{};

	auto jugador = tablero[p_ini.x][p_ini.y]->GetJugador();

	tablero[p_fin.x][p_fin.y] = tablero[p_ini.x][p_ini.y]; // la posición final apuntará a lo que apuntaba la posición inicial
	tablero[p_ini.x][p_ini.y] = &ninguna; // la posición inicial se queda vacía

	// busca la pieza que ha movido para actualizar sus coordenadas
	switch (jugador) {
	case B:
		for (auto&p : piezas_neg) {
			if (p.GetPosicion() == p_ini)p.actualizar_coordenadas(p_fin);
		}
		break;

	case W:
		for (auto&p : piezas_bla) {
			if (p.GetPosicion() == p_ini)p.actualizar_coordenadas(p_fin);
		}
		break;

	default:break;
	}

}
void Tablero::mover_pieza(Pieza&_p, Vector2D p_fin) {

	auto p_ini = _p.GetPosicion();
	tablero[p_fin.x][p_fin.y] = tablero[p_ini.x][p_ini.y]; // la posición final apuntará a lo que apuntaba la posición inicial
	tablero[p_ini.x][p_ini.y] = &ninguna; // la posición inicial se queda vacía

	// busca la pieza que ha movido para actualizar sus coordenadas
	switch (tablero[p_fin.x][p_fin.y]->GetJugador()) {
	case B:
		for (auto& p : piezas_neg) {
			if (p.GetPosicion() == p_ini)p.actualizar_coordenadas(p_fin);
		}
		break;

	case W:
		for (auto& p : piezas_bla) {
			if (p.GetPosicion() == p_ini)p.actualizar_coordenadas(p_fin);
		}
		break;

	default:break;
	}

}
// activa el evento captura en una posición determinada
void Tablero::activar_captura(Vector2D _posicion) { 
	auto jugador = tablero[_posicion.x][_posicion.y]->GetJugador();

	tablero[_posicion.x][_posicion.y]->set_captura(); // la pieza que estaba primero en esa posición será capturada
	tablero[_posicion.x][_posicion.y] = &ninguna; // cuando la pieza es capturada, ningún puntero volverá a apuntar a ella

	//borrar_pieza_capturada(jugador); // lo siguiente es borrar la pieza capturada
}
void Tablero::borrar_pieza_capturada(Jugador _jugador) {
	int num_capturadas=0, nuevo_num_piezas;
	vector<Pieza>piezas_copia{};

	switch (_jugador) {
	case W:
		nuevo_num_piezas = piezas_bla.size() - num_capturadas;
		piezas_copia = piezas_bla; // hacemos una copia de las piezas
		piezas_bla.clear(); // borramos el vector de piezas

		// volvemos a llenar el vector, sólo con las que no están capturadas
		for (auto p : piezas_copia) {
			if (!p.GetCapturada()) {
				piezas_bla.push_back(p);
			}
		}
		// nos cargamos los puestos libres que quedan al final
		while (piezas_bla.size() > nuevo_num_piezas) piezas_bla.pop_back();
		break;

	case B:
		nuevo_num_piezas = piezas_neg.size() - num_capturadas;
		piezas_copia = piezas_neg; // copiamos el vector y borramos el original
		piezas_neg.clear();
		
		// volvemos a llenar el vector, sólo con las que no están capturadas
		for (auto p : piezas_copia) {
			if (!p.GetCapturada()) {
				piezas_neg.push_back(p);
			}
		}
		// nos cargamos los puestos libres que quedan al final
		while (piezas_neg.size() > nuevo_num_piezas) piezas_neg.pop_back();
		break;

	default:break;
	}

}

// Funciones de prueba
void Tablero::vaciar() {
	// vacía el tablero
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			if (tablero[i][j] == nullptr)continue;
			else tablero[i][j] = &ninguna;
		}
	}
	// borra todas la piezas;
	piezas_bla.clear();
	piezas_neg.clear();
}
void Tablero::crear_pieza(Tipo _tipo, Jugador _jugador, Vector2D _posicion) {
	if (_tipo == no_hay) return void{};
	switch (_jugador) {
	case B: piezas_neg.push_back(Pieza(_posicion, _jugador, _tipo));
		tablero[_posicion.x][_posicion.y] = &(piezas_neg.at(piezas_neg.size() - 1));
		break;
	case W: piezas_bla.push_back(Pieza(_posicion, _jugador, _tipo));
		tablero[_posicion.x][_posicion.y] = &(piezas_bla.at(piezas_bla.size() - 1));
		break;
	}
}