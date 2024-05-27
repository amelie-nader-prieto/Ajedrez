#include "GLTablero.h"

void GLTablero::init() {
	//habilitar luces y definir perspectiva
	/*
		
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
	*/

}

void GLTablero::dibuja(int Estadoskin) {
	int r_oscuro, g_oscuro, b_oscuro;
	int r_claro, g_claro, b_claro;
	std::string skin = "default";
	std::string direccionF = "";


	switch (Estadoskin)
	{
	case 1: //Default
		skin = "default";
		r_oscuro = 0; g_oscuro = 0; b_oscuro = 0;
		r_claro = 255; g_claro = 255; b_claro = 255;
		break;
	case 2: //StarWars
		skin = "StarWars";
		r_oscuro = 0; g_oscuro = 100; b_oscuro = 162;
		r_claro = 249; g_claro = 245; b_claro = 220;
		break;
	case 3: //AnimalCrossing
		skin = "AnimalCrossing";
		r_oscuro = 107; g_oscuro = 142; b_oscuro = 35;
		r_claro = 255; g_claro = 227; b_claro = 232;
		break;
	}

	direccionF = "bin/imagenes/" + skin + "/Fondo.png";
	const char* rutaF = direccionF.c_str();
	int sum = 0;
	for (int i = 0; i < COLUMNA; i++) {
		for (int j = 0; j < FILA; j++) {
			sum = i + j;
			switch (j)
			{
			case 0: if (sum > 3 && sum < 7) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 1: if (sum > 3 && sum < 9) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 2: if (sum > 3 && sum < 11) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 3: if (sum > 3 && sum < 13) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 4: if (sum > 3 && sum <= 14) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 5: if (sum > 4 && sum <= 15) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 6: if (sum > 6 && sum < 16) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 7: if (sum > 8 && sum < 16) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 8: if (sum > 10 && sum < 16) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			case 9: if (sum > 12 && sum < 16) { cas.dibuja(i, j, r_oscuro, g_oscuro, b_oscuro, r_claro, g_claro, b_claro); cas.dibujaGrid(i, j); }break;
			default:
				break;

			}
		}
	}


	////////////Imagen de fondo////////////////
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(rutaF).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(-3.33, -1.2);
	glTexCoord2d(1, 1); glVertex2d(13.24, -1.2);
	glTexCoord2d(1, 0); glVertex2d(13.24, 11.18);
	glTexCoord2d(0, 0); glVertex2d(-3.33, 11.18);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//////////////////////////////////////////////////////
	 // Habilita las texturas y vincula la textura cargada
	

	/////////////OPCIONAL MARCO DEL TABLERO////////////////
	/*
		struct coordenadas {
		float x, y;
	};
	coordenadas limite1{ 12.0f,11.0f }, limite2{-1.0f,-1.0f};
	int r1 = 57; //55;
	int g1 = 59; //71; 
	int b1 = 73; //92;
	int r2 = 155;
	int g2 = 148;
	int b2 = 148;

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
	//glDisable(GL_LIGHTING);
	ETSIDI::setTextColor(0.84, 0.45, 0.1);//(1, 0, 0.5);//(1,0.6,1); //85.0f, 224.0f, 68.0f
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
	//glEnable(GL_LIGHTING);
}

void GLTablero::MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey) {

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
	world2cell(posX, posY, xcell_sel, ycell_sel);

	//capture other mouse events

	if (down) {
		controlKey = ctrlKey;
		shiftKey = sKey;
	}
	else {
		controlKey = shiftKey = false;
	}

	if (button == MOUSE_LEFT_BUTTON)
		leftButton = down;
	else if (button == MOUSE_RIGHT_BUTTON)
		rightButton = down;
	else if (button == MOUSE_MIDDLE_BUTTON)
		midButton = down;
	///////////////////////////

		//***WRITE ACTIONS CONNECTED TO MOUSE STATE HERE

		//print cell coordinates after click
	if (down)
		std::cout << "(" << xcell_sel << "," << ycell_sel << ")" << std::endl;
}