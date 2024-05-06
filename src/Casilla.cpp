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

void Casilla::dibujaGrid(int i, int j) {
	glLineWidth(2);
	glColor3ub(231,0,0);
	glBegin(GL_LINES);
	glVertex3f(i + 1, j + 1, 0.01f); glVertex3f(i + 1, j, 0.01f);
	glVertex3f(i + 1, j, 0.01f);	 glVertex3f(i, j, 0.01f);
	glVertex3f(i, j, 0.01f);		 glVertex3f(i, j + 1, 0.01f);
	glVertex3f(i, j + 1, 0.01f);  	 glVertex3f(i + 1, j + 1, 0.01f);

	/*
		glVertex2f(4, 0); glVertex2f(7, 0);
	glVertex2f(3, 1); glVertex2f(8, 1);
	glVertex2f(2, 2); glVertex2f(9, 2);
	glVertex2f(1, 3); glVertex2f(10, 3);
	glVertex3f(0, 4, 0.01f); glVertex3f(11, 4, 0.01f);
	glVertex3f(0, 5, 0.01f); glVertex3f(11, 5, 0.01f);
	glVertex3f(0, 6, 0.01f); glVertex3f(11, 6, 0.01f);
	glVertex3f(1, 7, 0.01f); glVertex3f(10, 7, 0.01f);
	glVertex3f(2, 8, 0.01f); glVertex3f(9, 8, 0.01f);
	glVertex3f(3, 9, 0.01f); glVertex3f(8, 9, 0.01f);	
	glVertex3f(4, 10, 0.01f); glVertex3f(7, 10, 0.01f);
	/////////////////////////////////////////////////////////
	glVertex3f(0, 4, 0.01f); glVertex3f(0, 6, 0.01f);
	glVertex3f(1, 3, 0.01f); glVertex3f(1, 7, 0.01f);
	glVertex3f(2, 2, 0.01f); glVertex3f(2, 8, 0.01f);
	glVertex3f(3, 1, 0.01f); glVertex3f(3, 9, 0.01f);
	glVertex3f(4, 0, 0.01f); glVertex3f(4, 10, 0.01f);
	glVertex3f(5, 0, 0.01f); glVertex3f(5, 10, 0.01f);
	glVertex3f(6, 0, 0.01f); glVertex3f(6, 10, 0.01f);
	glVertex3f(7, 0, 0.01f); glVertex3f(7, 10, 0.01f);
	glVertex3f(8, 1, 0.01f); glVertex3f(8, 9, 0.01f);
	glVertex3f(9, 2, 0.01f); glVertex3f(9, 8, 0.01f);
	glVertex3f(10, 3, 0.01f); glVertex3f(10, 7, 0.01f);
	glVertex3f(11, 4, 0.01f); glVertex3f(11, 6, 0.01f);
	*/

	glEnd();
	

}