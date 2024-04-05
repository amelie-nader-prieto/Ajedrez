#include "Pieza.h"

// Posición inicial de las piezas
//estas funciones son para el ajedrez BALBO
int Pieza::fila_inicial(Tipo t, Color c, int num) {
	if (t == Tipo::A) {
		return (c == Color::B ?
			(num == 1 ? 0 : 1) : (num == 1 ? 9 : 8));
	}
	else {
		return ((t == Tipo::R || t == Tipo::D) ?
			(c == Color::B ? 0 : 9) : ((t == Tipo::C || t == Tipo::T) ?
				(c == Color::B ? 1 : 8) : (c == Color::B ? 2 : 7))
			);
	}
}
int Pieza::columna_inicial(Tipo t, int num) {
	switch (t) {
	case Tipo::R:return 4; break;
	case Tipo::D:return 6; break;
	case Tipo::A:return 5; break;
	case Tipo::C:return (num == 1 ? 4 : 6); break;
	case Tipo::T:return (num == 1 ? 3 : 7); break;
	case Tipo::P:return num - 1; break;
	}
}

Pieza::Pieza(Color opc, Tipo t, int num) {
	color = opc;
	ubi_fila = fila_inicial(t, opc, num);
	ubi_columna = columna_inicial(t, num);
	ubi_prox = vector<int>{};
	buffer_coordenadas = vector<int>{};
}
Pieza::Pieza(Color opc, int fila, int columna) {
	color = opc;
	ubi_fila = fila;
	ubi_columna = columna;
	ubi_prox = vector<int>{};
	buffer_coordenadas = vector<int>{};
}

void Pieza::actualizar_coordenadas() {
	ubi_fila = ubi_prox[0];
	ubi_columna = ubi_prox[1];
	ubi_prox.clear();
}
