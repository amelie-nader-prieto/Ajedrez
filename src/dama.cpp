#include "dama.h"
//#include "pieza.h" //no hace falta

Dama::Dama(int fila, int columna,Jugador j) :
	Pieza(fila, columna, D,j) {
}
void Dama::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteReinaB.setCenter(0.05, 0.15);
		spriteReinaB.setSize(1, 1.2); //Esto se va ajustando segun como se vea la imagen
		spriteReinaB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteReinaN.setCenter(0.15, 0.1);
		spriteReinaN.setSize(1.3, 1.3);
		spriteReinaN.flip(true, true);
		spriteReinaN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}