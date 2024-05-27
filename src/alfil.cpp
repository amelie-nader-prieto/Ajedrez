#include "alfil.h"
//#include "pieza.h" //no hace falta

Alfil::Alfil(int fila, int columna,Jugador j) :
	Pieza(fila, columna, A, j ) {

}
void Alfil::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteAlfilB.setCenter(-0.05, 0.01);
		spriteAlfilB.setSize(0.9, 0.9); //Esto se va ajustando segun como se vea la imagen
		spriteAlfilB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteAlfilN.setCenter(-0.05, -0.1);
		spriteAlfilN.setSize(0.8, 0.9);
		spriteAlfilN.flip(true, true);
		spriteAlfilN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}
