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
// Operador para imprimir los colores (b ó n)
static std::ostream& operator<<(std::ostream& co, const Jugador&_jugador) {

    switch (_jugador) {
    case B:co << "n"; break; // negro
    case W:co << "b"; break; // blanco
    default:break;
    }

    return co;
}
// Operador para imprimir las casillas con número y letra
static std::ostream& operator<<(std::ostream &co, const Casilla& _casilla) {
    vector<char>letras_columnas = { 'a','b','c','d','e','f','g','h','i','j','k' };
    int num_fila_0 = 10;
    co << letras_columnas.at(_casilla.col) << num_fila_0 - _casilla.row;

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

// Devuelve la casilla en la que está una pieza, para imprimirla
static Casilla obtener_casilla(Pieza _p) {
    Casilla c;
    c.row = _p.GetFila();
    c.col = _p.GetColumna();
    return c;
}

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
static vector<Casilla>obtener_posibles_movimientos(Pieza _p) {
    vector<Casilla>v{};
    vector<Dir_t>direcciones{}; // posibles direcciones, se inicializa según la pieza
    vector<Vector2D>direcciones_caballo = { // posibles direcciones, sólo para C
            {-2,-1},{-2,1},{2,-1},{2,1},
            {-1,-2},{-1,2},{1,-2},{1,2}
    };

    Casilla c_actual{ _p.GetFila(),_p.GetColumna() };
    Casilla c_buffer{ c_actual }; // crea una copia de las coordenadas actuales para iterar sobre ellas sin modificarlas
    Casilla c_siguiente{}; // coordenadas siguientes según la dirección
    Casilla c_siguiente_2{}; // solo usar en el caso del caballo

    
    bool pieza_tuya_en_medio=false;
    bool pieza_rival_en_medio = false;

    switch (_p.GetTipo()) {
    case no_hay:break; // omite la pieza nula
    case A:
        // el alfil se mueve por las diagonales
        direcciones = { Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };

        for (const auto& p : direcciones) {
            do {
                pieza_tuya_en_medio = false;
                pieza_rival_en_medio = false;

                siguienteCasilla(p, c_buffer, c_siguiente);

                //condiciones para NO incluir la casilla siguiente
                if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;
                
                // verifica si hay una pieza en la casilla siguiente
                switch (_p.GetJugador()) {
                case B:
                    for (auto& p : piezas_neg) {
                        // comprueba si hay pieza tuya
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_tuya_en_medio = true;
                    }
                    for (auto& p : piezas_bla) {
                        // comprueba si hay pieza rival 
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                    }
                    break;
                case W:
                    for (auto& p : piezas_bla) {
                        // comprueba si hay pieza tuya
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col)pieza_tuya_en_medio = true;
                    }
                    for (auto& p : piezas_neg) {
                        // comprueba si hay pieza rival
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                    }
                    break;
                default:break;
                }

                if (pieza_tuya_en_medio)continue; // si hay una pieza tuya, se la salta

                v.push_back(c_siguiente);
                if (pieza_rival_en_medio)continue; // si hay una pieza rival, la añade y se la salta

                c_buffer = c_siguiente;

            } while (!(c_siguiente.row < 0 || c_siguiente.row == FILA || c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)));
            c_buffer = c_actual;
        }
        break;

    case T:
        // la torre se mueve en línea recta
        direcciones= { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT };

        for (const auto& p : direcciones) {
            pieza_tuya_en_medio = false;
            pieza_rival_en_medio = false;

            do {
                siguienteCasilla(p, c_buffer, c_siguiente);
                //condiciones para no incluir la casilla siguiente
                if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

                // verifica si hay una pieza en la casilla siguiente
                switch (_p.GetJugador()) {
                case B:
                    for (auto& p : piezas_neg) {
                        // comprueba si hay pieza tuya
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_tuya_en_medio = true;
                    }
                    for (auto& p : piezas_bla) {
                        // comprueba si hay pieza rival 
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                    }
                    break;
                case W:
                    for (auto& p : piezas_bla) {
                        // comprueba si hay pieza tuya
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col)pieza_tuya_en_medio = true;
                    }
                    for (auto& p : piezas_neg) {
                        // comprueba si hay pieza rival
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                    }
                    break;
                default:break;
                }

                if (pieza_tuya_en_medio)break; // si hay pieza tuya, se la salta

                v.push_back(c_siguiente);
                if (pieza_rival_en_medio)break; // si hay una pieza rival, la añade y se la salta
                c_buffer = c_siguiente;

            } while (!(c_siguiente.row < 0 || c_siguiente.row == FILA || c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)));
            c_buffer = c_actual;
        }
        break;

    case D:
        // la dama se mueve en las diagonales y en línea recta
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };

        for (const auto& p : direcciones) {
            pieza_tuya_en_medio = false;
            pieza_rival_en_medio = false;

            do {
                siguienteCasilla(p, c_buffer, c_siguiente);
                //condiciones para no incluir la casilla siguiente
                if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

                // verifica si hay una pieza en la casilla siguiente
                switch (_p.GetJugador()) {
                case B:
                    for (auto& p : piezas_neg) {
                        // comprueba si hay pieza tuya
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_tuya_en_medio = true;
                    }
                    for (auto& p : piezas_bla) {
                        // comprueba si hay pieza rival 
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                    }
                    break;
                case W:
                    for (auto& p : piezas_bla) {
                        // comprueba si hay pieza tuya
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col)pieza_tuya_en_medio = true;
                    }
                    for (auto& p : piezas_neg) {
                        // comprueba si hay pieza rival
                        if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                    }
                    break;
                default:break;
                }

                if (pieza_tuya_en_medio)break; // si hay pieza tuya, se la salta


                v.push_back(c_siguiente);
                if (pieza_rival_en_medio)break; // si hay una pieza del rival, se la salta
                c_buffer = c_siguiente;

            } while (!(c_siguiente.row < 0 || c_siguiente.row == FILA || c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)));
            c_buffer = c_actual;
        }
        break;

    case R:
        // el rey se mueve en vertical, horizontal y diagonal, pero SÓLO avanza una casilla
        direcciones = { Dir_t::UP,Dir_t::DOWN,Dir_t::RIGHT,Dir_t::LEFT,Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };

        for (const auto& p : direcciones) {
            pieza_tuya_en_medio = false;

            siguienteCasilla(p, c_buffer, c_siguiente);
            //condiciones para no incluir la casilla siguiente
            if ((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;

            // verifica si hay una pieza en la casilla siguiente
            switch (_p.GetJugador()) {
            case B:
                for (auto& p : piezas_neg) {
                    // comprueba si hay pieza tuya
                    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_tuya_en_medio = true;
                }
                for (auto& p : piezas_bla) {
                    // comprueba si hay pieza rival 
                    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                }
                break;
            case W:
                for (auto& p : piezas_bla) {
                    // comprueba si hay pieza tuya
                    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col)pieza_tuya_en_medio = true;
                }
                for (auto& p : piezas_neg) {
                    // comprueba si hay pieza rival
                    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
                }
                break;
            default:break;
            }

            if (pieza_tuya_en_medio)break; // si hay pieza tuya, se la salta

            v.push_back(c_siguiente);
        }
        break;

    case C:
        // movimiento del caballo - no sigue las primitivas de movimiento

        for (auto p : direcciones_caballo) {
            pieza_tuya_en_medio = false;

            c_siguiente = { c_actual.row + p.x,c_actual.col + p.y };

            // verifica si hay una pieza en la casilla de destino
            switch (_p.GetJugador()) {
            case B:
                for (auto& p : piezas_neg) {
                    // comprueba si hay pieza tuya
                    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_tuya_en_medio = true;
                }
                break;
            case W:
                for (auto& p : piezas_bla) {
                    // comprueba si hay pieza tuya
                    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col)pieza_tuya_en_medio = true;
                }
                break;
            default:break;
            }

            // verifica que se cumplan las condiciones para poder mover a esa casilla
            if (
                !(pieza_tuya_en_medio) && (
                    !((c_siguiente.row < 0 || c_siguiente.row == FILA ||
                        c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col))))
                )v.push_back(c_siguiente);

        }
       
        //for (auto p : { -2,2 }) {
        //    for (auto u : { -1,1 }) {

        //        pieza_tuya_en_medio = false;

        //        c_siguiente = { c_actual.row + p,c_actual.col + u };
        //        c_siguiente_2 = { c_actual.row + u,c_actual.col + p };

        //        // verifica si hay una pieza en la casilla siguiente
        //        switch (_p.GetJugador()) {
        //        case B:
        //            for (auto& p : piezas_neg) {
        //                // comprueba si hay pieza tuya
        //                if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_tuya_en_medio = true;
        //            }
        //            //for (auto& p : piezas_bla) {
        //            //    // comprueba si hay pieza rival 
        //            //    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
        //            //}
        //            break;
        //        case W:
        //            for (auto& p : piezas_bla) {
        //                // comprueba si hay pieza tuya
        //                if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col)pieza_tuya_en_medio = true;
        //            }
        //            //for (auto& p : piezas_neg) {
        //            //    // comprueba si hay pieza rival
        //            //    if (p.GetFila() == c_siguiente.row && p.GetColumna() == c_siguiente.col) pieza_rival_en_medio = true;
        //            //}
        //            break;
        //        default:break;
        //        }

        //        /*if ((c_siguiente.row < 0 || c_siguiente.row >= ROWS ||
        //            c_siguiente.col < 0 || c_siguiente.col >= COLUMNS || no_se_usa(c_siguiente.row, c_siguiente.col)))continue;
        //        else v.push_back(c_siguiente);*/
        //        if (
        //            !(pieza_tuya_en_medio) && (
        //                !((c_siguiente.row < 0 || c_siguiente.row == FILA ||
        //                    c_siguiente.col < 0 || c_siguiente.col == COLUMNA || no_se_usa(c_siguiente.row, c_siguiente.col))))
        //            )v.push_back(c_siguiente);

        //        pieza_tuya_en_medio = false;

        //        // verifica si hay una pieza en la casilla siguiente
        //        switch (_p.GetJugador()) {
        //        case B:
        //            for (auto& p : piezas_neg) {
        //                // comprueba si hay pieza tuya
        //                if (p.GetFila() == c_siguiente_2.row && p.GetColumna() == c_siguiente_2.col) pieza_tuya_en_medio = true;
        //            }
        //            break;
        //        case W:
        //            for (auto& p : piezas_bla) {
        //                // comprueba si hay pieza tuya
        //                if (p.GetFila() == c_siguiente_2.row && p.GetColumna() == c_siguiente_2.col)pieza_tuya_en_medio = true;
        //            }
        //            break;
        //        default:break;
        //        }

        //        if (
        //            !pieza_tuya_en_medio && (
        //                !((c_siguiente_2.row < 0 || c_siguiente_2.row == FILA ||
        //                    c_siguiente_2.col < 0 || c_siguiente_2.col == COLUMNA || no_se_usa(c_siguiente_2.row, c_siguiente_2.col))))
        //            )v.push_back(c_siguiente_2);

        //    }
        //    pieza_tuya_en_medio = false;
        //}

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

        switch (_p.GetJugador()) {
        case B: //Negro
            siguienteCasilla(Dir_t::UP, c_buffer, c_siguiente);
            v.push_back(c_siguiente);

            if (!_p.get_ha_movido()) {
                c_buffer = c_siguiente;
                siguienteCasilla(Dir_t::UP, c_buffer, c_siguiente);
                v.push_back(c_siguiente);
            }

            break;
        case W: //blanco
            siguienteCasilla(Dir_t::DOWN, c_buffer, c_siguiente);
            v.push_back(c_siguiente);

            if (!_p.get_ha_movido()) {
                c_buffer = c_siguiente;
                siguienteCasilla(Dir_t::DOWN, c_buffer, c_siguiente);
                v.push_back(c_siguiente);
            }
        }
        break;

    }

    return v;
}

/* INICIALIZAR PIEZAS */
//Esta función hace que cuando se quiera iniciar una pieza se manda el tipo y dirección 
static void iniciar(Tipo tipo, Vector2D posicion, Jugador j)
{

    switch (tipo)
    {
    case D:
        Tablero[posicion.x][posicion.y] = new Dama(posicion.x, posicion.y, j);
        break;
    case P:
        Tablero[posicion.x][posicion.y] = new Peon(posicion.x, posicion.y, j);
        break;
    case T:
        Tablero[posicion.x][posicion.y] = new Torre(posicion.x, posicion.y, j);
        break;
    case C:
        Tablero[posicion.x][posicion.y] = new Caballo(posicion.x, posicion.y, j);
        break;
    case R:
        Tablero[posicion.x][posicion.y] = new Rey(posicion.x, posicion.y, j);
        break;
    case A:
        Tablero[posicion.x][posicion.y] = new Alfil(posicion.x, posicion.y, j);
        break;
    case no_hay:
        Tablero[posicion.x][posicion.y] = new No_pieza(posicion.x, posicion.y);
        break;
    default:
        break;
    }

    if (Tablero[posicion.x][posicion.y]->GetTipo() != no_hay) {
        switch (Tablero[posicion.x][posicion.y]->GetJugador()) {
        case B:piezas_neg.push_back(*Tablero[posicion.x][posicion.y]); break;
        case W:piezas_bla.push_back(*Tablero[posicion.x][posicion.y]); break;
        default:break;
        }
    }
   

}

/* INICIALIZAR TABLERO */
// Función para crear el tablero al principio de la partida, con las piezas en sus sitios correspondientes
/* Como el tablero es una matriz de punteros a pieza, las opciones son:
* Si está fuera del rombo o está vacía, se inicializa como nullptr
* Si hay una pieza en esa casilla, se inicializa para que apunte a un objeto determinado del vector piezas_bla o piezas_neg
*/
static void iniciar_tablero() {
    
    // Peones
    for (int i = 2; i <= 8; i++)
    {
        iniciar(P, { 2,i }, B);//creación peones (negro)
        iniciar(P, { 7,i }, W);//creación peones (blanco)
    }

    // Creación de las fichas en la fila intermedia
    // T C A C T
    vector<Tipo>tipos_fila_intermedia{ T,C,A,T,C };
    int j = 3;
    for (const auto& p : tipos_fila_intermedia) {
        iniciar(p, { 1,j }, B); // creación fichas (negro)
        iniciar(p, { 8,j }, W); // creación fichas (blanco)
        j++;
    }

    // Creación de las fichas de la fila del fondo
    // R A D
    vector<Tipo>tipos_fila_3{ R,A,D };
    j = 4;
    for (const auto& p : tipos_fila_3) {
        iniciar(p, { 0,j }, B); // creación fichas (negro)
        iniciar(p, { 9,j }, W); // creación fichas (blanco)
        j++;
    }

}

//En esta función se mandará la pieza y se dará la dirección final 
static void cambio_casilla(Pieza& pieza, Vector2D final) {

    // No permite acceder a casillas que se salgan del tablero o del rombo
    if (no_se_usa(final.x, final.y) ||
        (final.x < 0 || final.y < 0 || final.x >= COLUMNA || final.y >= FILA)) {
        return void{};
    }

    bool movimiento_posible = false;

    // No permite acceder a casillas que no estén entre los movimientos permitidos de la pieza
    for (const auto& p : obtener_posibles_movimientos(pieza)) {
        if (final.x == p.row && final.y == p.col) {
            movimiento_posible = true;
            break;
        }
    }

    if (!movimiento_posible)return void{};

    Vector2D inicio = pieza.GetPosicion();

    // la casilla en la que estabas se queda vacía
    iniciar(no_hay, { inicio }, B);
    // vuelve a crear la pieza en la posición final
    iniciar(pieza.GetTipo(), { final }, pieza.GetJugador());

    pieza = *Tablero[final.x][final.y];
    
    if (!pieza.get_ha_movido()) pieza.set_ha_movido();

}