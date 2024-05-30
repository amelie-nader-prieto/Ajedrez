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

	void dibuja(int i, int j, int ro, int go, int bo, int rc, int gc, int bc) {
		int sum = i + j;
		glDisable(GL_LIGHTING);
		if (sum % 2) glColor3ub(rc, gc, bc); //para casillas pares un color mas claro//glColor3ub(23, 31, 161);
		else glColor3ub(ro, go, bo);//glColor3ub(126, 128, 156);
		glBegin(GL_POLYGON);
		glVertex2f((float)i + 1, (float)j + 1); //antihorario 
		glVertex2f((float)i + 1, (float)j);
		glVertex2f((float)i, (float)j);
		glVertex2f((float)i, (float)j + 1);
		glEnd();
		glEnable(GL_LIGHTING);
	}
  
	void dibujaGrid(int i, int j) {
		glLineWidth(2);
		glColor3ub(231, 0, 0);
		glBegin(GL_LINES);
		glVertex3f((float)i + 1.0f, (float)j + 1, 0.01f); glVertex3f((float)i + 1.0f, (float)j, 0.01f);
		glVertex3f((float)i + 1.0f, (float)j, 0.01f);	 glVertex3f((float)i, (float)j, 0.01f);
		glVertex3f((float)i, (float)j, 0.01f);		 glVertex3f((float)i, j + 1.0f, 0.01f);
		glVertex3f((float)i, (float)j + 1, 0.01f);  	 glVertex3f(i + 1.0f, j + 1.0f, 0.01f);
		glEnd();
	}
};



