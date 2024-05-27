#include "rey.h"
#include "pieza.h"

Rey::Rey(int fila, int columna,Jugador j) :
	Pieza(fila, columna, R,j) {
}
void Rey::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteReyB.setCenter(0.05, 0.15);
		spriteReyB.setSize(1, 1.2); //Esto se va ajustando segun como se vea la imagen
		spriteReyB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteReyN.setCenter(0, -0.05);
		spriteReyN.setSize(1, 1);
		spriteReyN.flip(true, true);
		spriteReyN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}