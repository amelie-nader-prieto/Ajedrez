#include "LogicaAjedrez.h"


// Dibuja el tablero en la consola
void dibujar(Tablero tab);

// Te da una lista de todas las piezas que hay en el tablero
// consulta la interfaz PÚBLICA del tablero
void lista_piezas(Tablero tab);
// Te da una lista de los sitios a los que se puede mover una pieza (la inicializa y te la da)
void lista_posibles_movimientos(Pieza p,Tablero tab,vector<Vector2D>& lista);
// Dibuja el tablero y da una lista de las piezas que hay
void imprime_info_tablero(Tablero tab);
// Dibuja el tablero y da una lista de las piezas que hay
// te da la lista accediendo a lo público y luego a lo privado
// la uso para ver si los datos se actualizan bien
void imprime_info_tablero_completa(Tablero tab);
// Representa sobre el tablero las posiciones a las que se puede mover
// [.] si se puede mover
// [x] si puede capturar
void imprime_movimientos_pieza(Pieza p, Tablero tab, vector<Vector2D>& lista);

// imprime las piezas (hace una copia de los datos PRIVADOS del tablero)
void lista_piezas_privada(Tablero tab);

// Bucle para mover una pieza a una casilla que elijas
// Uso esta función para comprobar si se mueven bien
void probar_movimientos_pieza(Pieza& p, Tablero& tab);

/*int main() {
	// Vamos a crear unos tableros de prueba
	Tablero tab_prueba_jaque, tab_prueba_jaque2;
	tab_prueba_jaque.vaciar(); tab_prueba_jaque2.vaciar();
	
	auto posicion_rey_1 = Vector2D(3,3); // variar este valor para ver si el rey en cuestión está amenazado o no
	auto posicion_rey_2 = Vector2D(6,6); // variar este valor para ver si el rey en cuestión está amenazado o no

	tab_prueba_jaque.crear_pieza(T, B, { 1,3 });
	tab_prueba_jaque.crear_pieza(T, B, { 8,3 });
	tab_prueba_jaque.crear_pieza(R, W, posicion_rey_1); 
	
	tab_prueba_jaque2.crear_pieza(A, B, { 5,7 });
	tab_prueba_jaque2.crear_pieza(R, W, posicion_rey_2);




	auto& posicion_rey = posicion_rey_1;
	Tablero& tab = tab_prueba_jaque;
	Pieza& mi_Rb = *tab[posicion_rey];

	dibujar(tab);
	cout << '\n' << mi_Rb;
	if (amenazado(mi_Rb.GetPosicion(), tab)) {
		cout << " (amenazado)\n";
	}
	vector<Vector2D>lugar_amenaza{};
	if (amenazado(mi_Rb.GetPosicion(), tab, lugar_amenaza)) {
		cout << "  la amenaza está en: ";
		for (auto p : lugar_amenaza) cout << "   " << p;
	}

	auto movs = obtener_posibles_movimientos(posicion_rey, tab);
	cout << "\nte puedes mover a: ";
	for (auto p : movs)cout << "   " << p;
	cout << '\n';

	//vector<Vector2D>sitios_ok{}; // se rellenará con las casillas en las que ya no estaría amenazado

	//auto tab_copia = new Tablero; *tab_copia = tab;
	//for (auto p : movs) {
	//	mover_pieza(posicion_rey, p, *tab_copia);
	//	if (!amenazado(p, *tab_copia)) sitios_ok.push_back(p);
	//	*tab_copia = tab;
	//}

	auto sitios_ok = sitios_sin_amenaza(posicion_rey, tab);

	cout << "los lugares en los que NO estarías amenazado serían: ";
	for (auto p : sitios_ok) cout << "   " << p;


	

	return 0;

	
}
*/
void dibujar(Tablero tab) {
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			if (tab.tablero[i][j])
				cout << "[" << tab.tablero[i][j]->GetTipo() << "]";
			else // si es null es porque no se usa
				cout << "   ";
		}
		cout << ' ' << FILA - i << '\n';
	}
	cout << " a  b  c  d  e  f  g  h  i  j  k" << '\n';
	cout << '\n';
}
void lista_piezas(Tablero tab) {
	cout << "\n---LISTA DE PIEZAS (PÚBLICA)---\n";
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			// comprobamos si se han creado las piezas correctamente
			if (tab.tablero[i][j]) {
				if (tab.tablero[i][j]->GetTipo() != no_hay) {
					cout << "(" << i << ',' << j << ")" << '\t';
					cout << (*tab.tablero[i][j]) << '\t';
				}
			}
		}
	}
	cout << "\n--------------------------------\n\n";
}
void lista_posibles_movimientos(Pieza p,Tablero tab, vector<Vector2D>& lista) {
	//auto movimientos = obtener_posibles_movimientos(*(tab.tablero[5][5]), tab);
	auto movimientos = obtener_posibles_movimientos(p.GetPosicion(), tab);
	int indice = 1;
	cout << "\n------------"<< p <<"------------\n";
	cout << "---------puede moverse a:-------\n";
	if (movimientos.size() == 0)cout << "...ningún sitio xd";
	else for (const auto& p : movimientos) {
		cout << indice << ". ";
		cout << p << '\t';
		indice++;
	}
	cout << "\n-----------------------------\n\n";
	//cout << "\n\n";
	lista = movimientos;
}


void lista_piezas_privada(Tablero tab) {
	auto lista_bla = tab.get_piezas_bla();
	auto lista_neg = tab.get_piezas_neg();
	int tam = (lista_bla.size() > lista_neg.size()) ?
		lista_bla.size() : lista_neg.size();
	cout << "\n--LISTA DE PIEZAS (PRIVADAS)--\n";
	cout << "  NEGRO  \t  BLANCO\n";
	for (int i = 0; i < tam; i++) {
		if (i < lista_neg.size()) cout << lista_neg.at(i);
		else cout << "         ";

		cout << '\t';

		if (i < lista_bla.size())cout << lista_bla.at(i);
		else cout << "         ";

		cout << '\n';
	}
	cout << "\n------------------------------\n\n";
}

void imprime_info_tablero(Tablero tab) {
	dibujar(tab);
	lista_piezas(tab);
}
void imprime_info_tablero_completa(Tablero tab) {
	
	imprime_info_tablero(tab);
	lista_piezas_privada(tab);

}
void imprime_movimientos_pieza(Pieza p, Tablero tab,vector<Vector2D>&lista) {
	
	//vector<Vector2D>v{};
	Vector2D posicion_pieza = p.GetPosicion();
	Vector2D posicion_actual;
	auto movimientos = obtener_posibles_movimientos(posicion_pieza, tab);
	bool posible_movimiento = false;

	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			posicion_actual = { i,j };
			posible_movimiento = false;
			if (!tab.tablero[i][j]) // si es null es porque no se usa
				cout << "   ";
			else { // resto de casillas que sí se usan
				if (posicion_actual==posicion_pieza)
					cout << "[" << tab.tablero[i][j]->GetTipo() << "]";
				else { // comprueba si la posicion actual pertenece a los posibles movimientos
					// si pertenece, la representa con un . o una x
					for (const auto& u : movimientos) {
						if (posicion_actual == u) {
							posible_movimiento = true;
							break;
						}
					}
					if (
						posible_movimiento &&
						hay_pieza_rival(Vector2D(i, j), p.GetJugador(), tab)
						) cout << "[x]";
					else if (posible_movimiento) cout << "[.]";
					else cout << "[ ]";
				}
			}
		}
		cout << ' ' << FILA - i << '\n';
	}
	cout << " a  b  c  d  e  f  g  h  i  j  k" << '\n';
	cout << '\n';
	lista_posibles_movimientos(*(tab.tablero[posicion_pieza.x][posicion_pieza.y]),tab,lista);
}

void probar_movimientos_pieza(Pieza& _pieza, Tablero& tab) {
	int opc = 0;
	vector<Vector2D>v{}; // aquí almacenará los posibles movimientos
	Vector2D posicion_destino; // posición a la que te vas a mover

	while (1) {
		v.clear(); opc = 0;
		imprime_movimientos_pieza(_pieza, tab, v);

		do {
			std::cin >> opc;
			if (opc == -1)return void{}; // -1 para salir del bucle
		} while (opc <= 0 || opc > v.size());
		posicion_destino = v.at(opc - 1);

		cout << '\n' << posicion_destino << "\n";
		
		mover_pieza(_pieza.GetPosicion(), posicion_destino, tab);
		imprime_info_tablero_completa(tab);
		cout << "\n\n";
	}
}