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
//static Pieza* tablero[FILA][COLUMNA];

static Pieza* Tablero[FILA][COLUMNA] = { nullptr };

/* Piezas blancas y negras */
// FALTA INICIALIZARLOS
static vector<Pieza>piezas_bla{}; // piezas que pertenecen al jugador blanco
static vector<Pieza>piezas_neg{}; // piezas que pertenecen al jugador negro

using Color = Jugador;

// Operador para imprimir los tipos de las piezas
static std::ostream& operator<< (std::ostream& co, const Tipo& t) {

    switch (t) {
    case no_hay:co << " "; break;
    case R:co << "R"; break;
    case D:co << "D"; break;
    case C:co << "C"; break;
    case A:co << "A"; break;
    case T:co << "T"; break;
    case P:co << "P"; break;
    }

    return co;
}

// CASILLAS QUE NO SE USAN
/*
* - De las filas 0 y 9: columnas 0 a 3 y 7 a 10
* - De las filas 1 y 8: columnas 0 a 2 y 8 a 10
* - De las filas 2 y 7: columnas 0, 1, 9 y 10
* - De las filas 3 y 6: columnas 0 y 10
*/
static bool no_se_usa(int i, int j) {
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
static enum class Dir_t {
    LEFT, UPLEFT, UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT
}; //primitivas de movimiento

/* A partir de una casilla y una dirección, te da las coordenadas
de la que sería la siguiente casilla*/
static void siguienteCasilla(Dir_t dir, Casilla ini, Casilla& fin) {
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
static vector<Casilla>obtener_posibles_movimientos(Pieza p) {
    vector<Casilla>v{};
    vector<Dir_t>direcciones{}; // posibles direcciones
    Casilla c_actual{ p.GetFila(),p.GetColumna() };
    Casilla c_buffer{ c_actual }; // crea una copia de las coordenadas actuales para iterar sobre ellas sin modificarlas
    Casilla c_siguiente{}; // coordenadas siguientes según la dirección

    switch (p.GetTipo()) {
    case no_hay:break; // omite la pieza nula
    case A:
        // el alfil se mueve por las diagonales
        direcciones = { Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
        for (const auto& p : direcciones) {
            do {
                siguienteCasilla(p, c_buffer, c_siguiente);

                //condiciones para NO incluir la casilla siguiente
                if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

                v.push_back(c_siguiente);
                c_buffer = c_siguiente;

            } while (!(c_siguiente.row < 0 || c_siguiente.row == FILA || c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)));
            c_buffer = c_actual;
        }
        break;

    case T:
        // la torre se mueve en línea recta
        direcciones= { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT };

        for (const auto& p : direcciones) {
            do {
                siguienteCasilla(p, c_buffer, c_siguiente);
                //condiciones para no incluir la casilla siguiente
                if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

                v.push_back(c_siguiente);
                c_buffer = c_siguiente;

            } while (!(c_siguiente.row < 0 || c_siguiente.row == FILA || c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)));
            c_buffer = c_actual;
        }
        break;

    case D:
        // la dama se mueve en las diagonales y en línea recta
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };

        for (const auto& p : direcciones) {
            do {
                siguienteCasilla(p, c_buffer, c_siguiente);
                //condiciones para no incluir la casilla siguiente
                if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

                v.push_back(c_siguiente);
                c_buffer = c_siguiente;

            } while (!(c_siguiente.row < 0 || c_siguiente.row == FILA || c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)));
            c_buffer = c_actual;
        }
        break;

    case R:
        // el rey se mueve en vertical, horizontal y diagonal, pero SÓLO avanza una casilla
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };

        for (const auto& p : direcciones) {
            siguienteCasilla(p, c_buffer, c_siguiente);
            //condiciones para no incluir la casilla siguiente
            if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

            v.push_back(c_siguiente);
        }
        break;

    case C:
        // movimiento del caballo - no sigue las primitivas de movimiento
        for (auto p : { -2,2 }) {
            for (auto u : { -1,1 }) {
                c_siguiente = { c_actual.row + p,c_actual.col + u };
                /*if ((c_siguiente.row < 0 || c_siguiente.row >= ROWS ||
                    c_siguiente.col < 0 || c_siguiente.col >= COLUMNS || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;
                else v.push_back(c_siguiente);*/
                if (
                    !((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                        c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))
                    )v.push_back(c_siguiente);

                c_siguiente = { c_actual.row + u,c_actual.col + p };
                /*if ((c_siguiente.row < 0 || c_siguiente.row >= ROWS ||
                    c_siguiente.col < 0 || c_siguiente.col >= COLUMNS || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;
                else v.push_back(c_siguiente);*/
                if (
                    !((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                        c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))
                    )v.push_back(c_siguiente);
            }
        }
        break;

    case P:
        /* AVANCE: El peón avanza una fila (o dos, si es su primer movimiento)
        * CAPTURA: Si hay una pieza del color opuesto en la fila siguiente y columna adyacente, puede capturarla (se moverá a la casilla en la que estaba esa pieza)
        * CAPTURA AL PASO: Si hay un peón del color opuesto:
        * - En su misma fila
        * - En una columna adyacente
        * - Que ha avanzado dos filas en el turno anterior
        * Puede capturarlo (se moverá a la casilla en la que estaría ese peón si sólo hubiese avanzado una fila)
        * PROMOCIÓN: Si ha llegado a la última o penúltima fila, DEBE promocionar, no puede avanzar más
        */

        switch (p.GetJugador()) {
        case B: //Negro
            siguienteCasilla(Dir_t::UP, c_buffer, c_siguiente);
            v.push_back(c_siguiente);
            break;
        case W: //blanco
            siguienteCasilla(Dir_t::DOWN, c_buffer, c_siguiente);
            v.push_back(c_siguiente);
        }
        break;

    }

    return v;
}

/* INICIALIZAR TABLERO */
// Función para crear el tablero al principio de la partida, con las piezas en sus sitios correspondientes
/* Como el tablero es una matriz de punteros a pieza, las opciones son:
* Si está fuera del rombo o está vacía, se inicializa como nullptr
* Si hay una pieza en esa casilla, se inicializa para que apunte a un objeto determinado del vector piezas_bla o piezas_neg
*/
//// ESTÁ INCOMPLETA
//void inicializar_tablero() {
//
//    for (int i = 0; i < FILA; i++) {
//        for (int j = 0; j < COLUMNA; j++) {
//            
//            if (no_se_usa(i, j) || (i >= 3 && i <= 6)) {
//                Tablero[i][j] = nullptr; continue;
//            }
//
//            if (i == 2 || i == 7) {
//                // Inicializar punteros a los peones
//                // i == 2 -> negros
//                // i == 7 -> blancos
//            }
//            else {
//                switch (j) {
//                case 3:
//                    // inicializar punteros a las torres
//                    // i == 1 -> negras
//                    // si no, blancas
//                    break;
//                case 4: // en la columna 4 hay reyes y caballos
//                    switch (i) {
//                    case 0: // rey negro
//                        break;
//                    case 1: // caballo negro
//                        break;
//                    case 8: // caballo blanco
//                        break;
//                    case 9: // rey blanco
//                        break;
//                    }
//                    break;
//
//                case 5: //alfiles
//                    // inicializar punteros a los alfiles
//                    break;
//
//                case 6: // en la columna 6 hay reinas y caballos
//                    switch (i) {
//                    case 0: // reina negra
//                        break;
//                    case 1: // caballo negro
//                        break;
//                    case 8: // caballo blanco
//                        break;
//                    case 9: // reina blanca
//                        break;
//                    }
//                    break;
//
//                case 7: // torres
//                    // inicializar punteros a las torres
//                    break;
//                }
//            }
//
//        }
//    }
//
//}
