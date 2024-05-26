#include "alfil.h"


Alfil::Alfil(int fila, int columna,Jugador j) :
	Pieza(fila, columna, A, j ) {

}

/*
vector <Vector2D> Alfil::obtener_posibles_movimientos(Tablero tab, vector<Vector2D>* posibles_movimientos{},
    vector<Dir_t>* direcciones, Vector2D* posicion_actual, Vector2D* posicion_buffer,
    Vector2D* posicion_siguiente, bool* fin_del_camino) {
    // el alfil se mueve por las diagonales
    *direcciones = { Dir_t::UPLEFT,Dir_t::UPRIGHT,Dir_t::DOWNLEFT,Dir_t::RIGHTDOWN };
    // Itera sobre las direcciones
    for (const auto& p : *direcciones) {

        // Itera sobre la MISMA direcci�n
        do {
            // inicializa la posici�n siguiente
            siguienteCasilla(p, *posicion_buffer, *posicion_siguiente);

            // si la posici�n siguiente es fin del camino, no la a�adir�
            *fin_del_camino = (
                omitir_posicion(*posicion_siguiente) ||
                hay_pieza_tuya(*posicion_siguiente, _p.GetJugador(), tab) ||
                hay_pieza_rival(*posicion_buffer, _p.GetJugador(), tab)
                ) ? true : false;
            // si no es fin del camino, la a�adir�
            if (!*fin_del_camino) posibles_movimientos.push_back(posicion_siguiente);

            // antes de pasar a la direcci�n siguiente, actualiza las coordenadas para seguir iterando
            *posicion_buffer = *posicion_siguiente;

        } while (!*fin_del_camino); // fin del bucle sobre la direcci�n
        posicion_buffer = posicion_actual;
    } // fin del bucle sobre todas las direcciones
}*/