#include "GLTablero.h"

//SOLO ES UNA PRUEBA
SpriteSequence spritePN{ "bin/imagenes/peon-negro.png", 1 };
SpriteSequence spritePB{ "bin/imagenes/peon-blanco.png", 1 };


void GLTablero::init() {
	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
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

	///////////////////FUENTES///////////////////////////
	float despx = 0.25, despy = 0.65f;
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

	//chess.dibujaPiezas();
	drawPieces(chess);
}


void GLTablero::MouseButton(int x, int y, int button, bool down, Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado) {

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
	//***WRITE ACTIONS CONNECTED TO MOUSE STATE HERE

	if (button == MOUSE_LEFT_BUTTON) {
		if (down)
		{
			if (seleccionado) {
				click_inicial = Vector2D{ xcell_sel, ycell_sel };
				seleccionado = false; //Para pasar a la seleccion de la posicion final
				std::cout << "incial seleccionada, ahora selecciona final" << std::endl;
			}
			else {
				click_final = Vector2D{ xcell_sel, ycell_sel };
				seleccionado = true; //Pra volver a seleccionar una pieza
				std::cout << "final seleccionado....espera movimiento" << std::endl;
				std::cout << "inicial: " << click_inicial << " final: " << click_final << std::endl;
				chess.mover_pieza(click_inicial, click_final); //intenta mover la pieza
				std::cout << "Deberia haber movido la pieza" << std::endl;
			}
			std::cout << "(" << xcell_sel << "," << ycell_sel << ")" << std::endl;
		}
		
	}
	
	
		
		
}


void GLTablero::drawPieces(Tablero& chess) {
	/*
		for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			//si hay una pieza en esta posicion la dibujamos
			if (chess.tablero[i][j] != nullptr && chess.tablero[i][j]->GetTipo() != no_hay) {
				chess.tablero[i][j]->dibuja();
			}

		}
	}
	*/


	//for (int i = 2; i < COLUMNA - 2; i++) {
	//chess.tablero[2][i]->dibuja();
	//chess.tablero[7][i]->dibuja();
	//}

	/*
		for (int i = 2; i < COLUMNA - 2; i++) {
		glPushMatrix();
		switch (chess.tablero[2][i]->GetTipo())
		{
		case no_hay:
			break;
		case R:
			break;
		case D:
			break;
		case C:
			break;
		case A:
			break;
		case T:
			break;
		case P:
			if (chess.tablero[2][i]->GetJugador() == Jugador::W) {
				glTranslatef(posicion.y, posicion.x - 0.05, 0.02);
				spritePB.setCenter(0, 0);
				spritePB.setSize(1, 0.9);
				spritePB.draw();
				glTranslatef(-posicion.y, -posicion.x + 0.05, -0.02);

			}

			if (jugador == Jugador::B) {

				glTranslatef(fila, columna - 0.05, 0.02);
				spritePN.setCenter(0, 0);
				spritePN.setSize(1, 0.9);
				spritePN.draw();
				glTranslatef(-fila, -columna + 0.05, -0.02);

			}
			break;
		default:
			break;
		}
	}
	glPopMatrix();
	*/

}
