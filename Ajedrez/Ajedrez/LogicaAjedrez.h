/*
* Este archivo contiene algunas cosas básicas,
* como constantes, tipos de datos específicos utilizados por varias clases, etc
*/

#pragma once
#include <vector>
using std::vector;

// dimensiones del tablero de ajedrez BALBO
#define ROWS 10
#define COLUMNS 11
/*
* Casillas que no se usan:
* - De las filas 0 y 9: columnas 0 a 3 y 7 a 10
* - De las filas 1 y 8: columnas 0 a 2 y 8 a 10
* - De las filas 2 y 7: columnas 0, 1, 9 y 10
* - De las filas 3 y 6: columnas 0 y 10
*/

enum class Color :char {
	B,W
};
enum class Tipo :char {
	R,D,A,C,T,P
};