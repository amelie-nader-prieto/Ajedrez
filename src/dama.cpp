#include "dama.h"
#include "pieza.h"

Dama::Dama(int fila, int columna,Jugador j) :
	Pieza(fila, columna, D,j) {
}

void Dama::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteB.setCenter(0, 0);
		spriteB.setSize(1, 0.9);
		spriteB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteN.setCenter(0, 0);
		spriteN.setSize(1, 0.9);
		spriteN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}