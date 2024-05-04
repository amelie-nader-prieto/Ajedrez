#include "GLTablero.h"

void GLTablero::dibuja() {
	int sum = 0;
	for (int i = 0; i < COLUMNA; i++) {
		for (int j = 0; j < FILA; j++) {
			sum = i + j;
			switch (j)
			{
			case 0: if (sum > 3 && sum < 7) cas.dibuja(i, j); break;
			case 1: if (sum > 3 && sum < 9) cas.dibuja(i, j); break;
			case 2: if (sum > 3 && sum < 11) cas.dibuja(i, j); break;
			case 3: if (sum > 3 && sum < 13) cas.dibuja(i, j); break;
			case 4: if (sum > 3 && sum <= 14) cas.dibuja(i, j); break;
			case 5: if (sum > 4 && sum <= 15) cas.dibuja(i, j); break;
			case 6: if (sum > 6 && sum < 16) cas.dibuja(i, j); break;
			case 7: if (sum > 8 && sum < 16) cas.dibuja(i, j); break;
			case 8: if (sum > 10 && sum < 16) cas.dibuja(i, j); break;
			case 9: if (sum > 12 && sum < 16) cas.dibuja(i, j); break;
			default:
				break;
			}
		}
	}

	////////////Imagen de fondo///////////// 
	gluLookAt(5, 5, 17,  // posicion del ojo
		5.0, 5.0, 0.0,   // hacia que punto mira  
		0.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/opcional2.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2f(-7, -6);
	glTexCoord2d(1, 1); glVertex2f(27, -6);
	glTexCoord2d(1, 0); glVertex2f(27, 23);
	glTexCoord2d(0, 0); glVertex2f(-7, 23);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////


}