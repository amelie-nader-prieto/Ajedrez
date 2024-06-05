#pragma once

#include "Tablero.h"

// DIRECCIONES
/*
* Las ocho direcciones del espacio
* UP = sumar 1 a la fila, DOWN = restar 1 a la fila
* RIGHT = sumar a la columna, LEFT = restar a la columna
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
* Función más elaborada, para descartar una posible posición automáticamente
* - Si es de las que no se usan, no te puedes mover ahí
* - Si se sale de los índices válidos, no te puedes mover ahí
*/
inline bool omitir_posicion(const Vector2D& _posicion) {
    return (_posicion.x < 0 || _posicion.y < 0 ||
        _posicion.x == FILA || _posicion.y == COLUMNA ||
        no_se_usa(_posicion.x, _posicion.y)) ? true : false;
}


// FUNCIONES QUE REVISAN EL TABLERO
/* Revisan los datos públicos de la clase Tablero
// hay que pasarles el objeto Tablero junto con los demás parámetros */
/* Para saber si hay una pieza de tu color en una casilla determinada */
bool hay_pieza_tuya(Vector2D _posicion, Jugador _jugador, Tablero tab);

/* Para saber si hay una pieza del color opuesto en una casilla determinada */
bool hay_pieza_rival(Vector2D _posicion, Jugador _jugador, Tablero tab);

/* Para saber si se cumplen las condiciones para que un peón (pasado como argumento) haga una captura tradicional
* Podrá hacer una captura tradicional si hay una pieza rival en la fila siguiente en diagonal
*/
bool condiciones_captura_peon(Pieza _peon, Tablero tab);
/*
* Para saber si se cumplen las condiciones para una captura al paso
* Si el peón de un jugador avanza dos filas, en el turno siguiente se llamará a
esta función para evaluar la posibilidad del jugador opuesto de capturar dicho peón.
* ARGUMENTOS:
* Tablero
* Posición del peón que acaba de avanzar dos filas (si es true, dicho peón podrá ser capturado en ese turno)
* posicion_posible_capturador: si la función es true, se inicializará con la posición del peón qe podrá captuar en ese turno
* Es un vector en caso de que por un casual haya varios posibles capturadores
*/
bool condiciones_captura_al_paso(Pieza posible_peon_capturado, Tablero tab, vector<Vector2D>posicion_posible_capturador);
/* CONDICIONES DE PROMOCIÓN DEL PEÓN
* Promociona sólo a caballo o alfil si llega a la fila última en las columnas c, i (columnas 2 y 8)
* Promociona a caballo, alfil, dama o torre si llega a la fila última en las columnas d-h (columnas 3-7)
* En las columnas a y k (columnas 0 y 9) no hay promoción.
*/
bool condiciones_promocion(Pieza peon);
/* Verifica si un rey está amenazado
* Está amenazado si su posición actual se encuentra entre los
* posibles movimientos de alguna de las piezas del rival
*/
bool amenazado(Vector2D casilla, Tablero tab);
// Esta sobrecarga además te da un vector con las posiciones de las piezas que están amenazando a tu rey
// la manera de salir del jaque es o moviendo a tu rey o capturando a alguna de esas piezas
bool amenazado(Vector2D casilla, Tablero tab, vector<Vector2D>& piezas_que_lo_amenazan);
/*
* Al iniciar el turno, verifica si hay jaque mate
* Concretamente, comprueba:
* - Si el rey está amenazado
* - Si tiene jugadas legales
* En caso de que esté amenazado y NO tenga jugadas legales, hay jaque mate
*/
bool condiciones_jaque_mate(Tablero tab,Jugador&derrotado);
/* Para saber si alguna de tus piezas (comprobando entre todas tus piezas) puede moverse a una casilla determinada
* (se usa para evaluar si hay jaque mate)
*/
bool casilla_accesible(Vector2D casilla, Jugador jugador, Tablero tab);
/*
* Te dice si un jugador determinado está ahogado
* (El ahogado se produce si el jugador de quien es el turno no tiene jugadas legales y su rey no está en jaque)
*/
bool ahogado(Jugador jugador, Tablero tab);

// FUNCIONES QUE HACEN COPIAS DEL TABLERO
/*
* Si un rey está amenazado, esta función te dará los lugares a los que éste se puede mover legalmente
* (es decir, los lugares en los que dejará de estar amenazado, entre sus posibles movimientos)
* ARGUMENTOS:
* - casilla: posición del rey amenazado
* - el tablero
*/
vector<Vector2D>sitios_sin_amenaza(Vector2D casilla, Tablero tab);
/*
* Te da todas las casillas a las que podría moverse una pieza QUE SEAN LEGALES
* (es decir, de entre sus posibles movimientos, aquellos que no pongan a su propio rey en jaque)
*/
vector<Vector2D>obtener_movimientos_legales(Vector2D casilla, Tablero tab);

/*
* Para saber si se cumplen las condiciones para una captura al paso
* Si el peón de un jugador avanza dos filas, en el turno siguiente se llamará a
esta función para evaluar la posibilidad del jugador opuesto de capturar dicho peón.
* ARGUMENTOS:
* Tablero
* Posición del peón que acaba de avanzar dos filas (si es true, dicho peón podrá ser capturado en ese turno)
* posicion_posible_capturador: si la función es true, se inicializará con la posición del peón qe podrá captuar en ese turno
* Es un vector en caso de que por un casual haya varios posibles capturadores
*/
bool condiciones_captura_al_paso(Pieza posible_peon_capturado, Tablero tab, vector<Vector2D>posicion_posible_capturador);

/* CONDICIONES DE PROMOCIÓN DEL PEÓN
* Promociona sólo a caballo o alfil si llega a la fila última en las columnas c, i (columnas 2 y 8)
* Promociona a caballo, alfil, dama o torre si llega a la fila última en las columnas d-h (columnas 3-7)
* En las columnas a y k (columnas 0 y 9) no hay promoción.
*/
bool condiciones_promocion(Pieza peon);



// FUNCIONES DE MOVIMIENTO
/*
* A partir de una posición y una dirección, te da las coordenadas
* de la posición siguiente
*/
void siguienteCasilla(Dir_t dir, Vector2D ini, Vector2D& fin);
/*
* Te da todas las posiciones a las que podría moverse dicha pieza
* Hay que pasarle también el tablero, ya que necesitará revisar
* dónde están todas las demás
*/
vector<Vector2D>obtener_posibles_movimientos(Pieza _p, Tablero tab);
/*
* Te da todas las posiciones a las que podría moverse una pieza
* A partir de su posición y del tablero
* Usad esta si podéis. A mí al menos me ha dado menos problemas
*/
vector<Vector2D>obtener_posibles_movimientos(Vector2D casilla, Tablero tab);
/* Para mover una pieza
* Incluye la lógica de la captura (tienen que coincidir dos piezas opuestas en la posición de destino)
*/
void mover_pieza(Vector2D p_ini, Vector2D p_fin, Tablero&tab);
/* Para mover una pieza
* Incluye la lógica de la captura (tienen que coincidir dos piezas opuestas en la posición de destino)
*/
void mover_pieza(Vector2D p_ini, Vector2D p_fin, Tablero& tab);





// INICIALIZAR PIEZAS

/*
* Esta función hace que cuando se quiera iniciar una pieza se manda el tipo y dirección
*/
static void iniciar(Tipo tipo, Vector2D posicion, Jugador j,Tablero tab);

// Liberar la memoria al final del programa
void liberar_memoria(Tablero tab);