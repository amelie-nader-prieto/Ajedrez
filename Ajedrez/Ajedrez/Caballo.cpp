#include "Caballo.h"

Caballo::Caballo(Color opc, int num) :
	Pieza(opc, Tipo::C, num) {
	capturado = false;
	promocionado = false;
	num_caballo = num;
}
Caballo::Caballo(Color opc, int fila, int columna) :
	Pieza(opc, fila, columna) {
	capturado = false;
	promocionado = true;
	num_caballo = 3;
}