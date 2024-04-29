#include "pieza.h"

#include "Tipos_piezas.h"


Tipo Pieza:: GetTipo() {
	return tipo;
}

Vector2D Pieza::GetPosicion()
{
	return direccion;
}