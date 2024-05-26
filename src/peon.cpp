#include "peon.h"


Peon::Peon(int fila, int columna,Jugador j) :
	Pieza(fila, columna, P,j){}


bool Peon::posible_captura_al_paso( Peon p) {

    if( (jugador != p.jugador)&&(p.en_captura==true))
    {
        return true;
    }

    return false;
}

void Peon::cuando_en_captura() {
    if (primer_movimiento == true)
    {

    }

}