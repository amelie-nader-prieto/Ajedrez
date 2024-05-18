#pragma once
#include <iostream>
#include"freeglut.h"

class Casilla
{
public:
    int row, col;
    //row: fila - va de 0 a 9
    //col: coluna - va de 0 a 10
    void imprime() {
        std::cout << "( " << row << " , " << col << " )" << std::endl;
    }

	void dibuja(int i, int j) {
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
  
	void dibujaGrid(int i, int j) {
		glLineWidth(2);
		glColor3ub(231, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(i + 1, j + 1, 0.01f); glVertex3f(i + 1, j, 0.01f);
		glVertex3f(i + 1, j, 0.01f);	 glVertex3f(i, j, 0.01f);
		glVertex3f(i, j, 0.01f);		 glVertex3f(i, j + 1, 0.01f);
		glVertex3f(i, j + 1, 0.01f);  	 glVertex3f(i + 1, j + 1, 0.01f);
		glEnd();
	}
};



