#include "Reina.h"

Reina::Reina(Color opc) :
	Pieza(opc, Tipo::D, 1) {
	capturada = false;
	promocionada = false;
}
Reina::Reina(Color opc, int fila, int columna) :
	Pieza(opc, fila, columna) {
	capturada = false;
	promocionada = true;
}