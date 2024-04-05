#include "Tablero.h"

Tablero::Tablero(int filas, int columnas) {
	vector<Casilla>fila{};
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			Casilla c(
				(i % 2 == 0 && j % 2 == 0) ||
				(i % 2 != 0 && j % 2 != 0) ?
				(Color::W) : (Color::B)
			);
			fila.push_back(c);
		}
		tablero.push_back(fila);
		fila.clear();
	}
}

int Tablero::size_rows() {
	return tablero.size();
}
int Tablero::size_columns() {
	return tablero[0].size();
}

Casilla Tablero::getCasilla(int fila, int col) {
	return tablero[fila][col];
}
vector<Casilla>Tablero::getFila(int num) {
	return tablero[num];
}
vector<Casilla>Tablero::getColumna(int num) {
	vector<Casilla>columna{};
	for (int i = 0; i < tablero.size(); i++) {
		columna.push_back(tablero[i][num]);
	}
	return columna;
}
vector<Casilla>Tablero::getAdyacentes(int fila, int columna) {
	vector<Casilla>adyacentes{};
	vector<int>v{ -1,0,1 };
	for (auto p : v) {
		for (auto u : v) {
			if (columna + u<0 || columna + u>tablero[0].size()
				|| fila + p<0 || fila + p>tablero.size()
				|| (p == 0 && u == 0))continue;
			adyacentes.push_back(tablero[fila + p][columna + u]);
		}
	}
	return adyacentes;
}