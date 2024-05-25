#include "GLTablero.h"

void GLTablero::init() {
	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
}

void GLTablero::dibuja() {
	int sum = 0;
	for (int i = 0; i < COLUMNA; i++) {
		for (int j = 0; j < FILA; j++) {
			sum = i + j;
			switch (j)
			{
			case 0: if (sum > 3 && sum < 7) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 1: if (sum > 3 && sum < 9) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 2: if (sum > 3 && sum < 11) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 3: if (sum > 3 && sum < 13) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 4: if (sum > 3 && sum <= 14) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 5: if (sum > 4 && sum <= 15) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 6: if (sum > 6 && sum < 16) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 7: if (sum > 8 && sum < 16) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 8: if (sum > 10 && sum < 16) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
			case 9: if (sum > 12 && sum < 16) { cas.dibuja(i, j); cas.dibujaGrid(i, j); }break;
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
	glTexCoord2d(0, 1); glVertex3f(-3.5, -2, -0.1);
	glTexCoord2d(1, 1); glVertex3f(14, -2, -0.1);
	glTexCoord2d(1, 0); glVertex3f(14, 12, -0.1);
	glTexCoord2d(0, 0); glVertex3f(-3.5, 12, -0.1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////

	///////////////////FUENTES///////////////////////////
	float despx = 0.25, despy = 0.65f;
	ETSIDI::setTextColor(1, 1, 0); //85.0f, 224.0f, 68.0f
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


void GLTablero::MouseButton(int x, int y, int button, bool down) {

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


	//finally cell coordinates
	world2cell(posX, posY, xcell_sel, ycell_sel); //método para pasar las coordenadas a posiciones de las casillas


	//catura eventos del mouse
	if (button == MOUSE_LEFT_BUTTON)
		leftButton = down;
	
		//***WRITE ACTIONS CONNECTED TO MOUSE STATE HERE




		//print cell coordinates after click
	//if (down && !no_se_usa(xcell_sel, ycell_sel)) //revisar, imprime algunas casillas y otras no
	if (down)
		std::cout << "(" << xcell_sel << "," << ycell_sel << ")" << std::endl;
}