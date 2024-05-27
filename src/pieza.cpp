#include "pieza.h"
#include "Tipos_piezas.h"

#include <iostream>
using std::cout;


//Esta función igualará las caracteristicas de una pieza con otra
void Pieza::igualar(const Pieza& otra) {
	posicion = otra.posicion;
	jugador = otra.jugador;
	tipo = otra.tipo;
	primer_movimiento = otra.primer_movimiento;
	capturada = otra.capturada;
}




