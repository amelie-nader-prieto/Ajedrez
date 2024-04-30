#include "pieza.h"

#include "Tipos_piezas.h"


Tipo Pieza:: GetTipo() {
	return tipo;
}

Vector2D Pieza::GetPosicion()
{
	return direccion;
}
int Pieza::GetFila() {
	return fila;
}
int Pieza::GetColumna() {
	return columna;
}
int Pieza::GetJugador() {
	return jugador;
}

void Pieza::SetFila(int _fila) {
	fila = _fila;
}
void Pieza::SetColumna(int _col) {
	columna = _col;
}
void Pieza::SetTipo(Tipo t) {
	tipo = t;
}
void Pieza::SetJugador(Jugador j) {
	jugador = j;
}