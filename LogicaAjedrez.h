#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "pieza.h"
#include "peon.h"
#include "dama.h"
#include "rey.h"
#include "torre.h"
#include "alfil.h"
#include "caballo.h"
#include "No_pieza.h"
#include "Casilla.h"

using std::vector;

// Dimensiones del tablero de ajedrez Balbo
#define FILA 10
#define COLUMNA 11

// Objeto TABLERO - se crea como vector de punteros a piezas
static Pieza* tablero[FILA][COLUMNA];

/* Piezas blancas y negras */
vector<Pieza>piezas_bla{}; // piezas que pertenecen al jugador blanco
vector<Pieza>piezas_neg{}; // piezas que pertenecen al jugador negro

// CASILLAS QUE NO SE USAN
/*
* - De las filas 0 y 9: columnas 0 a 3 y 7 a 10
* - De las filas 1 y 8: columnas 0 a 2 y 8 a 10
* - De las filas 2 y 7: columnas 0, 1, 9 y 10
* - De las filas 3 y 6: columnas 0 y 10
*/
bool no_se_usa(int i, int j) {
    return ((i == 0 || i == 9) && (((j >= 0 && j <= 3) || (j >= 7 && j <= 10)))
        || ((i == 1 || i == 8) && ((j >= 0 && j <= 2) || (j >= 8 && j <= 10)))
        || ((i == 2 || i == 7) && ((j == 0 || j == 1) || (j == 9 || j == 10)))
        || ((i == 3 || i == 6) && (j == 0 || j == 10))
        ) ? true : false;
}

// DIRECCIONES
/*
* Las ocho direcciones del espacio
* UP es sumar uno a la fila y es SUBIR, los peones BLANCOS avanzan en esta dirección
* DOWN es restar uno a la fila y en BAJAR, los peones NEGROS avanzan en esta dirección
*/
enum class Dir_t {
    LEFT, UPLEFT, UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT
}; //primitivas de movimiento

/* A partir de una casilla y una dirección, te da las coordenadas
de la que sería la siguiente casilla*/
void siguienteCasilla(Dir_t dir, Casilla ini, Casilla& fin) {
    // dir: dirección
    // ini: casilla de origen
    // fin: casilla de destino (por referencia)

    switch (dir)
    {
    case Dir_t::LEFT:
        fin.row = ini.row; fin.col = ini.col - 1;
        break;
    case Dir_t::UPLEFT:
        fin.row = ini.row + 1; fin.col = ini.col - 1;
        break;
    case Dir_t::UP:
        fin.row = ini.row + 1; fin.col = ini.col;
        break;
    case Dir_t::UPRIGHT:
        fin.row = ini.row + 1; fin.col = ini.col + 1;
        break;
    case Dir_t::RIGHT:
        fin.row = ini.row; fin.col = ini.col + 1;
        break;
    case Dir_t::RIGHTDOWN:
        fin.row = ini.row - 1; fin.col = ini.col + 1;
        break;
    case Dir_t::DOWN:
        fin.row = ini.row - 1; fin.col = ini.col;
        break;
    case Dir_t::DOWNLEFT:
        fin.row = ini.row - 1; fin.col = ini.col - 1;
        break;
    default:
        break;
    }
}

/* Devuelve todas las casillas a las que podría moverse una pieza.
* Por ahora tiene en cuenta
* - Su tipo (reglas de movimiento)
* - Que las casillas estén dentro del tablero y que queden dentro del rombo
*/
// ESTÁ SIN TERMINAR
// debería tener en cuenta la ubicación de las otras piezas
