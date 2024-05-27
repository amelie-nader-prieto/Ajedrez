#include "torre.h"
#include "pieza.h"

Torre::Torre(int fila, int columna,Jugador j) :
	Pieza(fila, columna, T,j) {

}
void Torre::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteTorreB.setCenter(-0.05, -0.01);
		spriteTorreB.setSize(0.9, 0.9); //Esto se va ajustando segun como se vea la imagen
		spriteTorreB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteTorreN.setCenter(-0.05, -0.02);
		spriteTorreN.setSize(0.9, 0.95);
		spriteTorreN.flip(true, true);
		spriteTorreN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}
