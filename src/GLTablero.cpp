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


	////////////Imagen de fondo////////////////
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/fondo3.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-3.5, -2,-0.1);
	glTexCoord2d(1, 1); glVertex3f(14, -2, -0.1);
	glTexCoord2d(1, 0); glVertex3f(14, 12,-0.1);
	glTexCoord2d(0, 0); glVertex3f(-3.5, 12,-0.1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////

	/////////////OPCIONAL MARCO DEL TABLERO////////////////7
	/*
	struct coordenadas {
		float x, y;
	};
	coordenadas limite1{ 12.0f,11.0f }, limite2{-1.0f,-1.0f};
	int r1 = 54;//57; //55;
	int g1 = 54;//59; //71; 
	int b1 = 54;//73; //92;
	int r2 = 124;//53;//155;
	int g2 =23;//55;//148;
	int b2 = 23;//65;//148;

	glBegin(GL_POLYGON);
	glColor3ub(r2, g2, b2); 
	glVertex3f(limite1.x - 0.1f, limite1.y - 0.1f, -0.08f);
	glVertex3f(limite2.x + 0.1f, limite1.y - 0.1f, -0.08f);
	glVertex3f(limite2.x + 0.1f, limite2.y + 0.1f, -0.08f);
	glVertex3f(limite1.x - 0.1f, limite2.y + 0.1f, -0.08f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(r1, g1, b1); 
	glVertex3f(limite1.x - 0.2f, limite1.y - 0.2f, -0.07f);
	glVertex3f(limite2.x + 0.2f, limite1.y - 0.2f, -0.07f);
	glVertex3f(limite2.x + 0.2f, limite2.y + 0.2f, -0.07f);
	glVertex3f(limite1.x - 0.2f, limite2.y + 0.2f, -0.07f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(r2, g2, b2);
	glVertex3f(limite1.x - 0.85f, limite1.y - 0.85f, -0.02f);
	glVertex3f(limite2.x + 0.85f, limite1.y - 0.85f, -0.02f);
	glVertex3f(limite2.x + 0.85f, limite2.y + 0.85f, -0.02f);
	glVertex3f(limite1.x - 0.85f, limite2.y + 0.85f, -0.02f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(r1, g1, b1);
	glVertex3f(limite1.x - 1.0f, limite1.y - 1.0f, -0.01f);
	glVertex3f(limite2.x + 1.0f, limite1.y - 1.0f, -0.01f);
	glVertex3f(limite2.x + 1.0f, limite2.y + 1.0f, -0.01f);
	glVertex3f(limite1.x - 1.0f, limite2.y + 1.0f, -0.01f);
	glEnd();

	*/
	

	///////////////////FUENTES///////////////
	float despx = 0.25, despy = 0.65f;
	ETSIDI::setTextColor(0,1,0); //85.0f, 224.0f, 68.0f
	ETSIDI::setFont("bin/fuentes/Tablero1.ttf", 18);
	glTranslatef(-despx, 0.4, 0);
	ETSIDI::printxy("  A", 0, -1);  ETSIDI::printxy("   B", 1, -1);
	ETSIDI::printxy("   C", 2, -1); ETSIDI::printxy("   D", 3, -1);
	ETSIDI::printxy("   E", 4, -1); ETSIDI::printxy("   F", 5, -1);
	ETSIDI::printxy("   G", 6, -1); ETSIDI::printxy("   H", 7, -1);
	ETSIDI::printxy("   I", 8, -1); ETSIDI::printxy("   J", 9, -1);
	ETSIDI::printxy("   K", 10, -1);
	glTranslatef(despx, -0.4, 0);
	glTranslatef(0, -despy, 0);
	ETSIDI::printxy("  1", -1, 1); ETSIDI::printxy("  2", -1, 2);
	ETSIDI::printxy("  3", -1, 3); ETSIDI::printxy("  4", -1, 4);
	ETSIDI::printxy("  5", -1, 5); ETSIDI::printxy("  6", -1, 6);
	ETSIDI::printxy("  7", -1, 7); ETSIDI::printxy("  8", -1, 8);
	ETSIDI::printxy("  9", -1, 9); ETSIDI::printxy("  10", -1, 10);
	glTranslatef(0, despy, 0);
}