#include "caballo.h"
//#include "pieza.h" //no hace falta

Caballo::Caballo(int fila, int columna,Jugador j) :
	Pieza(fila, columna, C,j) {

}
void Caballo::dibuja() {
	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteCaballoB.setCenter(-0.05, -0.01);
		spriteCaballoB.setSize(0.9, 0.9); //Esto se va ajustando segun como se vea la imagen
		spriteCaballoB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteCaballoN.setCenter(-0.05, -0.02);
		spriteCaballoN.setSize(0.9, 0.95);
		spriteCaballoN.flip(true, true);
		spriteCaballoN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}

