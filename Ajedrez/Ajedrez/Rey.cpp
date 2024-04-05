#include "Rey.h"

Rey::Rey(Color opc):
	Pieza(opc,Tipo::R,1) {
	amenazado = false;
}