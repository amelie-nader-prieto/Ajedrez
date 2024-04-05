#include "Peon.h"

Peon::Peon(Color opc, int num, int fila, int col) :
	Pieza(opc, Tipo::P, num) {
	promocionable = false;
	capturado = false;
	num_peon = num;
}

//los peones promocionan al llegar a la última o 
void Peon::checkProm() {
	switch (color) {
	case Color::B:promocionable = (ubi_fila == 8 || ubi_fila == 9) ? true : false; break;
	case Color::W:promocionable = (ubi_fila == 0 || ubi_fila == 1) ? true : false; break;
	}
}

//los peones siempre avanzan hacia delante en su fila
void Peon::coordenadas_avance() {
	switch (color) {
	case Color::B:ubi_prox[0] = ubi_fila + 1;
	case Color::W:ubi_prox[0] = ubi_fila - 1;
	}
}