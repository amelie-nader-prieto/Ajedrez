#include "Casilla.h"

void Casilla::dibuja(int i, int j) {
	int sum = i + j;
	glDisable(GL_LIGHTING);
	if (sum % 2) glColor3ub(216, 243, 220); //para casillas pares un color mas oscuro//glColor3ub(23, 31, 161);
	else glColor3ub(82, 183, 136);//glColor3ub(126, 128, 156);
	glBegin(GL_POLYGON);
	glVertex2f(i + 1, j + 1); //antihorario 
	glVertex2f(i + 1, j);
	glVertex2f(i, j);
	glVertex2f(i, j + 1);
	glEnd();
	glEnable(GL_LIGHTING);
}