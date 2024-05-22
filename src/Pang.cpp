#include "LogicaAjedrez.h"

// Te da una lista de todas las piezas que hay en el tablero
void lista_piezas(Tablero tab);
// Te da una lista de los sitios a los que se puede mover una pieza
void lista_posibles_movimientos(Pieza p,Tablero tab);
// Dibuja el tablero y da una lista
void imprime_info_tablero(Tablero tab);

int main(){
	// vamos a crear un tablero para ver si funciona bien
	Tablero tab;
	lista_piezas(tab);
	// por favor enlazador no me traiciones
	dibujar(tab);

	// vamos a probar a vaciar el tablero
	cout << "\nVaciamos el tablero:\n";
	tab.vaciar();
	dibujar(tab);
	lista_piezas(tab);

	// creamos algunas piezas para hacer pruebas
	cout << "\nCreamos algunas piezas:\n";
	tab.crear_pieza(P, W, { 5,4 });
	tab.crear_pieza(P, B, { 5,5 });
	dibujar(tab);
	lista_piezas(tab);

	// probamos a mover las piezas
	lista_posibles_movimientos(*tab.tablero[5][5], tab);
	tab.mover_pieza({ 5,5 }, obtener_posibles_movimientos(*tab.tablero[5][5], tab).at(0));

	imprime_info_tablero(tab);

	lista_posibles_movimientos(*tab.tablero[5][4], tab);
	tab.mover_pieza({ 5,4 }, obtener_posibles_movimientos(*tab.tablero[5][4], tab).at(0));
	imprime_info_tablero(tab);

	lista_posibles_movimientos(*tab.tablero[4][4], tab);

	//// vaciamos otra vez. probaremos con otro tipo de pieza
	tab.vaciar();
	tab.crear_pieza(D, B, { 5,5 });
	auto mi_pieza = *tab.tablero[5][5];
	imprime_info_tablero(tab);
	//auto v = obtener_posibles_movimientos(mi_pieza, tab);
	obtener_posibles_movimientos(*tab.tablero[5][5], tab);
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
void lista_posibles_movimientos(Pieza p,Tablero tab) {
	auto movimientos = obtener_posibles_movimientos(*(tab.tablero[5][5]), tab);
	int indice = 1;
	cout << p << " - " << "puede moverse a:\n";
	if (movimientos.size() == 0)cout << "...ningún sitio xd";
	else for (const auto& p : movimientos) {
		cout << indice << ". ";
		cout << p << '\n';
		indice++;
	}
	cout << "\n\n";
}
void imprime_info_tablero(Tablero tab) {
	dibujar(tab);
	lista_piezas(tab);
}