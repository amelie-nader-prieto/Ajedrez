#include "pieza.h"
#include "Tipos_piezas.h"

// Funciones de interfaz
Vector2D Pieza::GetPosicion() {
	return direccion; 
}
Tipo Pieza::GetTipo() {
	return tipo;
}
int Pieza::GetFila() {
	if (this == nullptr)return -1;
	return fila;
}
int Pieza::GetColumna() {
	return columna;
}
Jugador Pieza::GetJugador() {
	return jugador;
}

void Pieza::SetFila(int _fila) {
	fila = _fila;
}
void Pieza::SetColumna(int _columna) {
	columna = _columna;
}
void Pieza::SetTipo(Tipo t) {
	tipo = t;
}
void Pieza::SetJugador(Jugador t) {
	jugador = t;
}