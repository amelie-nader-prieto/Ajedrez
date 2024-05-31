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

	//Termina la ejecución del método "mover_pieza" si se detecta que no es el jugador al que le toca
    //mover la pieza (al que le toca el turno). Impide que el movimiento de la pieza se realice
	//if (tablero[p_ini.x][p_ini.y]->GetJugador() != turnoActual) {
		//No es el turno del Jugador que intenta mover la pieza
		//std::cout << "No es tu turno!" << std::endl;
		//return;
	//}




	auto jugador = tablero[p_ini.x][p_ini.y]->GetJugador();

	tablero[p_fin.x][p_fin.y] = tablero[p_ini.x][p_ini.y]; // la posición final apuntará a lo que apuntaba la posición inicial
	tablero[p_ini.x][p_ini.y] = &ninguna; // la posición inicial se queda vacía

	// busca la pieza que ha movido para actualizar sus coordenadas
	switch (jugador) {
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

	//Cambia el turno al otro jugador: Despues de mover la pieza y actualizar las coordenadas
//el turno se cambia al otro jugador, despues de cada movimiento válido el turno pasa al otro jugador
	//turnoActual = (turnoActual == W) ? B : W;

}

void Tablero::mover_pieza(Pieza& _p, Vector2D p_fin) {

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

void Tablero::activar_promocion(Vector2D _posicion) {
	auto jugador = (*this)[_posicion]->GetJugador();

	//tablero[_posicion.x][_posicion.y] = &ninguna; // la casilla que antes apuntaba al peón ahora apunta a ningún sitio (se vacía la casilla)

	// se crea una nueva pieza en dicha casilla

	// CASILLAS PARA SÓLO CABALLO Y ALFIL - columnas 2 y 8
	auto columna = _posicion.y;
	if (columna == 2 || columna == 8) /*promociona a alfil o caballo*/ {
		// que se pueda elegir entre C y A
		crear_pieza(C, jugador, _posicion);
	}

	// CASILLAS PARA LAS CUATRO PIEZAS POSIBLES - columnas de la 3 a la 7
	if (columna >= 3 && columna <= 7) {
		// que se pueda elegir entre D, C T y A
		crear_pieza(D, jugador, _posicion);
	}

}

void Tablero::activar_promocion(Vector2D _posicion, Tipo nuevo_tipo) {
	auto jugador = (*this)[_posicion]->GetJugador();
	auto columna = _posicion.y;

	(*this)[_posicion]->set_promocion();
	tablero[_posicion.x][_posicion.y] = &ninguna;

	// comprueba que el tipo al que se va a promocionar sea válido
	if (
		(nuevo_tipo == P || nuevo_tipo == R || nuevo_tipo == no_hay) || /*tipos no permitidos en general*/
		((columna == 2 || columna == 7) && (nuevo_tipo == D || nuevo_tipo == T)) /*en las columnas 2 y 8 sólo se promociona a C o A*/
		) nuevo_tipo = C;

	// CASILLAS PARA SÓLO CABALLO Y ALFIL - columnas 2 y 8
	if (columna == 2 || columna == 8) /*promociona a alfil o caballo*/ {
		// que se pueda elegir entre C y A
		crear_pieza(nuevo_tipo, jugador, _posicion);
	}

	// CASILLAS PARA LAS CUATRO PIEZAS POSIBLES - columnas de la 3 a la 7
	if (columna >= 3 && columna <= 7) {
		// que se pueda elegir entre D, C T y A
		crear_pieza(nuevo_tipo, jugador, _posicion);
	}


}

void Tablero::borrar_pieza_capturada(Jugador _jugador) {
	int num_capturadas = 0, nuevo_num_piezas;
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

void Tablero::dibujar() {
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			if (tablero[i][j]) 
				cout << "[" << tablero[i][j]->GetTipo() << "]";
			else // si es null es porque no se usa
				cout << "   ";
		}
		cout << ' ' << FILA - i << '\n';
	}
	cout << " a  b  c  d  e  f  g  h  i  j  k" << '\n';
}

void Tablero::mostrar_lista_de_piezas() {
	int num_piezas_max = (piezas_bla.size() > piezas_neg.size() ? piezas_bla.size() : piezas_neg.size());

	cout << "  BLANCO\t  NEGRO\n";
	for (int i = 0; i < num_piezas_max; i++) {
		if (i < piezas_bla.size()){
			cout << i + 1 << ". " << piezas_bla.at(i);
		}
		cout << "\t";
		if (i < piezas_neg.size()) {
			cout << i + 1 << ". " << piezas_neg.at(i);
		}
		cout << '\n';
	}
	/*cout << "  total blancas: " << piezas_bla.size();
	cout << "  total negras: " << piezas_neg.size();*/

}