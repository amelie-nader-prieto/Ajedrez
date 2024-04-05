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

enum class Color :char {
	B,W
};
enum class Tipo :char {
	R,D,A,C,T,P
};