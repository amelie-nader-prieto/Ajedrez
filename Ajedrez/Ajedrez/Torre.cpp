#include "Torre.h"

Torre::Torre(Color opc, int num) :
	Pieza(opc, Tipo::T, num) {
	capturada = false;
	promocionada = false;
	num_torre = num;
}
Torre::Torre(Color opc, int fila, int columna) :
	Pieza(opc, fila, columna) {
	capturada = false;
	promocionada = true;
	num_torre = 3;
}