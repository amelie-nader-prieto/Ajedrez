#include "Alfil.h"

Alfil::Alfil(Color opc, int num) :
	Pieza(opc, Tipo::A, num) {
	capturado = false;
	promocionado = false;
	num_alfil = num;
}
Alfil::Alfil(Color opc, int fila, int columna) :
	Pieza(opc, fila, columna) {
	capturado = false;
	promocionado = true;
	num_alfil = 3;
}