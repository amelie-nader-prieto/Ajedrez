#include "LogicaAjedrez.h"


// Dibuja el tablero en la consola
void dibujar(Tablero tab);

// Te da una lista de todas las piezas que hay en el tablero
void lista_piezas(Tablero tab);
// Te da una lista de los sitios a los que se puede mover una pieza
void lista_posibles_movimientos(Pieza p,Tablero tab,vector<Vector2D>& lista);
// Dibuja el tablero y da una lista de las piezas que hay
void imprime_info_tablero(Tablero tab);
// Representa las posiciones a las que se puede mover una pieza
void imprime_movimientos_pieza(Pieza p, Tablero tab, vector<Vector2D>& lista);
// Bucle para mover una pieza a una casilla que elijas
// Uso esta función para comprobar si se mueven bien
void probar_movimientos_pieza(Pieza& p, Tablero &tab);

int main(){
	// Creamos y configuramos tableros de prueba
	Tablero tab2;
	tab2.vaciar();
	tab2.crear_pieza(D, B, { 5,5 });
	
	auto &mi_pieza = *(tab2.tablero[5][5]);
	
	// Bucle para mover la pieza varias veces
	probar_movimientos_pieza(mi_pieza, tab2);
	
}

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
	cout << "\n-------LISTA DE PIEZAS-------\n";
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			// comprobamos si se han creado las piezas correctamente
			if (tab.tablero[i][j]) {
				if (tab.tablero[i][j]->GetTipo() != no_hay) {
					cout << "(" << i << ',' << j << ")" << '\t';
					cout << (*tab.tablero[i][j]) << '\n';
				}
			}
		}
	}
	cout << "\n-----------------------------\n\n";
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
void imprime_info_tablero(Tablero tab) {
	dibujar(tab);
	lista_piezas(tab);
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
void probar_movimientos_pieza(Pieza& _pieza, Tablero &tab) {
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
		tab.mover_pieza(_pieza, posicion_destino);

	}
}