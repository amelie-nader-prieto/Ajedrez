#pragma once

#include "Tablero.h"
#include <iostream>

using std::cout;

// operador para imprimir los tipos de piezas
inline std::ostream& operator<<(std::ostream& co, const Tipo& t) {

    switch (t) {
    case no_hay:co << " "; break;
    case R:co << "R"; break;
    case D:co << "D"; break;
    case C:co << "C"; break;
    case A:co << "A"; break;
    case T:co << "T"; break;
    case P:co << "P"; break;
    default:break;
    }

    return co;

}
// operador para imprimir el color de la pieza
inline std::ostream& operator<<(std::ostream& co, const Jugador& _jugador) {

    switch (_jugador) {
    case B:co << "n"; break; // negro
    case W:co << "b"; break; // blanco
    default:break;
    }

    return co;

}
// operador para imprimir las coordenadas con n�mero y letra
inline std::ostream& operator<<(std::ostream& co, const Vector2D& _casilla) {

    vector<char>letras_columnas = { 'a','b','c','d','e','f','g','h','i','j','k' };
    int num_fila_0 = 10;
    co << letras_columnas.at(_casilla.y) << num_fila_0 - _casilla.x;

    return co;

}
// operador para imprimir toda la info de la pieza
// (lo uso para comprobar que se han creado bien)
inline std::ostream& operator<<(std::ostream& co, Pieza& _pieza) {
    if (_pieza.GetTipo() == no_hay) return co;
    co << (_pieza.GetTipo()) << (_pieza.GetJugador()) << " en " << (_pieza.GetPosicion());
    return co;
}

// DIRECCIONES
/*
* Las ocho direcciones del espacio
* UP es sumar uno a la fila y es SUBIR, los peones BLANCOS avanzan en esta direcci�n
* DOWN es restar uno a la fila y en BAJAR, los peones NEGROS avanzan en esta direcci�n
*/
static enum class Dir_t {
    LEFT, UPLEFT, UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT
}; //primitivas de movimiento


// CASILLAS QUE NO SE USAN
/*
* Casillas que no se usan para que el tablero sea un rombo
* - De las filas 0 y 9: columnas 0 a 3 y 7 a 10
* - De las filas 1 y 8: columnas 0 a 2 y 8 a 10
* - De las filas 2 y 7: columnas 0, 1, 9 y 10
* - De las filas 3 y 6: columnas 0 y 10
*/
inline bool no_se_usa(int i, int j) {
    return ((i == 0 || i == 9) && (((j >= 0 && j <= 3) || (j >= 7 && j <= 10)))
        || ((i == 1 || i == 8) && ((j >= 0 && j <= 2) || (j >= 8 && j <= 10)))
        || ((i == 2 || i == 7) && ((j == 0 || j == 1) || (j == 9 || j == 10)))
        || ((i == 3 || i == 6) && (j == 0 || j == 10))
        ) ? true : false;
}

// POSICIONES A LAS QUE NO TE PUEDES MOVER
/*
* Funci�n m�s elaborada, para descartar una posible posici�n autom�ticamente
* - Si es de las que no se usan, no te puedes mover ah�
* - Si se sale de los �ndices v�lidos, no te puedes mover ah�
*/
inline bool omitir_posicion(const Vector2D& _posicion) {
    return (_posicion.x < 0 || _posicion.y < 0 ||
        _posicion.x == FILA || _posicion.y == COLUMNA ||
        no_se_usa(_posicion.x, _posicion.y)) ? true : false;
}


// FUNCIONES QUE REVISAN EL TABLERO
// Revisan los datos p�blicos de la clase Tablero
// hay que pasarles el objeto Tablero junto con los dem�s par�metros
/* Para saber si hay una pieza de tu color en una casilla determinada */
bool hay_pieza_tuya(Vector2D _posicion, Jugador _jugador, Tablero tab);
/* Para saber si hay una pieza del color opuesto en una casilla determinada */
bool hay_pieza_rival(Vector2D _posicion, Jugador _jugador, Tablero tab);
/* Para saber si se cumplen las condiciones para que un pe�n (pasado como argumento) haga una captura tradicional
* Podr� hacer una captura tradicional si hay una pieza rival en la fila siguiente en diagonal
*/
bool condiciones_captura_peon(Pieza _peon, Tablero tab);

// FUNCIONES DE MOVIMIENTO
/*
* A partir de una posici�n y una direcci�n, te da las coordenadas
* de la posici�n siguiente
*/
void siguienteCasilla(Dir_t dir, Vector2D ini, Vector2D& fin);
/*
* Te da todas las posiciones a las que podr�a moverse dicha pieza
* Hay que pasarle tambi�n el tablero, ya que necesitar� revisar
* d�nde est�n todas las dem�s
*/
vector<Vector2D>obtener_posibles_movimientos(Pieza _p, Tablero tab);


// INICIALIZAR PIEZAS
// Esta funci�n hace que cuando se quiera iniciar una pieza se manda el tipo y direcci�n 
static void iniciar(Tipo tipo, Vector2D posicion, Jugador j,Tablero tab);

// FUNCIONES DE DIBUJO DEL TABLERO (lo dibujan en la consola)
/*
* Dibuja el tablero en la consola, con todas las piezas
*/
void dibujar(Tablero tab);

// Liberar la memoria al final del programa
void liberar_memoria(Tablero tab);