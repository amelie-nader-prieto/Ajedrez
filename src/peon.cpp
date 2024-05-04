#include "peon.h"
//#include "pieza.h" //no hace falta incluir pieza.h porque ya se ha incluido en peon.h

Peon::Peon(int fila, int columna,Jugador j) :
	Pieza(fila, columna, P,j)
{
}

void Peon::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spritePeonB.setCenter(0, 0);
		spritePeonB.setSize(1, 0.9);
		spritePeonB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna-1, fila + 0.05 -1, 0);
		spritePeonN.setCenter(0, 0);
		spritePeonN.setSize(1, 0.9);
		//spritePeonN.flip(true, true);
		spritePeonN.draw();
		glTranslatef(-columna+1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}

