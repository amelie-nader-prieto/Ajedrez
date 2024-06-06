#include "GLTablero.h"

//SOLO ES UNA PRUEBA
//SpriteSequence spritePN{ "bin/imagenes/default/peon-negro.png", 1 };
//SpriteSequence spritePB{ "bin/imagenes/default/peon-blanco.png", 1 };


void GLTablero::init() {
	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
}


void GLTablero::dibuja_casillas(const int &Estadoskin) {

	int r_oscuro, g_oscuro, b_oscuro;
	int r_claro, g_claro, b_claro;
//	std::string skin = "default";
//	std::string direccionF = "";
	modo_musica_mov = Estadoskin; //Pra poner el sonido de movimiento de la pieza

	switch (Estadoskin)
	{
	case 1: //Default
	//	skin = "default";
		r_oscuro = 187; g_oscuro = 190; b_oscuro = 215;
		r_claro = 64; g_claro = 65; b_claro = 77;
		break;
	case 2: //StarWars
		//skin = "StarWars";
		r_oscuro = 249; g_oscuro = 245; b_oscuro = 220;
		r_claro = 0; g_claro = 100; b_claro = 162;
		break;
	case 3: //AnimalCrossing
		//skin = "AnimalCrossing";
		r_oscuro = 255; g_oscuro = 227; b_oscuro = 232;
		r_claro = 107; g_claro = 142; b_claro = 35;
		break;
	}

	//direccionF = "bin/imagenes/" + skin + "/Fondo.png";
//	const char* rutaF = direccionF.c_str();

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

	///////////////////FUENTES///////////////////////////
	float despx = 0.25f, despy = 0.65f;
	ETSIDI::setTextColor(0.84f, 0.45f, 0.1f);//(1, 0, 0.5);//(1,0.6,1); //85.0f, 224.0f, 68.0f
	ETSIDI::setFont("bin/fuentes/Tablero1.ttf", 18);
	glTranslatef(-despx, 0.4f, 0.0f);
	ETSIDI::printxy("  A", 0, -1);  ETSIDI::printxy("   B", 1, -1);
	ETSIDI::printxy("   C", 2, -1); ETSIDI::printxy("   D", 3, -1);
	ETSIDI::printxy("   E", 4, -1); ETSIDI::printxy("   F", 5, -1);
	ETSIDI::printxy("   G", 6, -1); ETSIDI::printxy("   H", 7, -1);
	ETSIDI::printxy("   I", 8, -1); ETSIDI::printxy("   J", 9, -1);
	ETSIDI::printxy("   K", 10, -1);
	glTranslatef(despx, -0.4f, 0.0f);
	glTranslatef(0.0f, -despy, 0.0f);
	ETSIDI::printxy("  1", -1, 1); ETSIDI::printxy("  2", -1, 2);
	ETSIDI::printxy("  3", -1, 3); ETSIDI::printxy("  4", -1, 4);
	ETSIDI::printxy("  5", -1, 5); ETSIDI::printxy("  6", -1, 6);
	ETSIDI::printxy("  7", -1, 7); ETSIDI::printxy("  8", -1, 8);
	ETSIDI::printxy("  9", -1, 9); ETSIDI::printxy("  10", -1, 10);
	glTranslatef(0.0f, despy, 0.0f);

	dibujaCasillasPosibles(movimientosPosibles, Vector2D{xcell_sel, ycell_sel});
	
	////////////////////////////////////////////////////

}


void GLTablero::MouseButton(int x, int y, int button, bool down,Tablero&tab,
	Vector2D& click_inicial, Vector2D& click_final, bool& seleccionado) {

	chess = tab;

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
				click_final = { xcell_sel, ycell_sel };
				click_inicial = { xcell_sel, ycell_sel };
				seleccionado = false; //Para pasar a la seleccion de la posicion final
				movimientosPosibles = obtener_posibles_movimientos(click_inicial, chess);
				//	std::cout << "Casilla inicial: "   <<std::endl;
			}
			else {
				click_final = { xcell_sel, ycell_sel };
				seleccionado = true; //Para volver a seleccionar una pieza
				//	std::cout << "Casilla final: "<<click_final << std::endl;
				chess.mover_pieza(click_inicial, click_final); //intenta mover la pieza
				//	std::cout << "Espera movimiento......Debería haber movido" << std::endl;
				movimientosPosibles.clear();

				switch (modo_musica_mov)
				{
				case 1: ETSIDI::play("bin/sonidos/Movimiento_pieza.wav");
					break;
				case 2: ETSIDI::play("bin/sonidos/StarWars/Matar.wav");
					break;
				case 3: ETSIDI::play("bin/sonidos/AnimalCrossing/Matar.wav");
					break;
				default:
					break;

				}
				//click_final = { 0,0 };
			}
			//std::cout << "(" << xcell_sel << "," << ycell_sel << ")" << std::endl;
		}
	}
}

void GLTablero::drawPieces(Tablero& chess, const int& Estadoskin) {

	std::string skin = "default";
	switch (Estadoskin)
	{
	case 1: skin = "default"; break;
	case 2: skin = "StarWars"; break;
	case 3: skin = "AnimalCrossing"; break;
	default: skin = "default"; break;
		break;
	}
	std::string direccionW = "";
	std::string direccionB = "";
	double CenterW_X{0}, CenterW_Y{0}, CenterB_X{0}, CenterB_Y{0};
	double SizeW_X{1}, SizeW_Y{0.9}, SizeB_X{1}, SizeB_Y{0.9};
	

	direccionB = "bin/imagenes/" + skin + "/ReyNegro.png";
	direccionW = "bin/imagenes/" + skin + "/ReyBlanco.png";
	const char* rutaB = direccionB.c_str();
	const char* rutaW = direccionW.c_str();
	SpriteSequence spriteReyN{ rutaB, 1 };
	SpriteSequence spriteReyB{ rutaW, 1 };

	direccionB = "bin/imagenes/" + skin + "/ReinaNegro.png";
	direccionW = "bin/imagenes/" + skin + "/ReinaBlanco.png";
	rutaB = direccionB.c_str();
	rutaW = direccionW.c_str();
	SpriteSequence spriteReinaN{ rutaB, 1 };
	SpriteSequence spriteReinaB{ rutaW, 1 };

	direccionB = "bin/imagenes/" + skin + "/CaballoNegro.png";
	direccionW = "bin/imagenes/" + skin + "/CaballoBlanco.png";
	rutaB = direccionB.c_str();
	rutaW = direccionW.c_str();
	SpriteSequence spriteCaballoN{ rutaB, 1 };
	SpriteSequence spriteCaballoB{ rutaW, 1 };

	direccionB = "bin/imagenes/" + skin + "/AlfilNegro.png";
	direccionW = "bin/imagenes/" + skin + "/AlfilBlanco.png";
	rutaB = direccionB.c_str();
	rutaW = direccionW.c_str();
	SpriteSequence spriteAlfilN{ rutaB, 1 };
	SpriteSequence spriteAlfilB{ rutaW, 1 };

	direccionB = "bin/imagenes/" + skin + "/TorreNegro.png";
	direccionW = "bin/imagenes/" + skin + "/TorreBlanco.png";
	rutaB = direccionB.c_str();
	rutaW = direccionW.c_str();
	SpriteSequence spriteTorreN{ rutaB, 1 };
	SpriteSequence spriteTorreB{ rutaW, 1 };

	direccionB = "bin/imagenes/" + skin + "/PeonNegro.png";
	direccionW = "bin/imagenes/" + skin + "/PeonBlanco.png";
	rutaB = direccionB.c_str();
	rutaW = direccionW.c_str();
	SpriteSequence spritePeonN{ rutaB, 1 };
	SpriteSequence spritePeonB{ rutaW, 1 };


	glPushMatrix();
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA ; j++) {
			if (chess.tablero[i][j] != nullptr && chess.tablero[i][j]->GetTipo() != no_hay) {

				switch (chess.tablero[i][j]->GetTipo())
				{
				case no_hay:
					break;
				case R:
					switch (Estadoskin)
					{
					case 1:
						//skin = "default";
						break;
					case 2:
						//skin = "StarWars";
						CenterW_X = 0.05; CenterW_Y = 0.15;
						SizeW_X = 1; SizeW_Y = 1.2;

						CenterB_X = 0; CenterB_Y = 0.05;
						SizeB_X = 1; SizeB_Y = 1;
						break;
					case 3:
						//skin = "AnimalCrossing";
						CenterW_X = 0.15; CenterW_Y = 0.3;
						SizeW_X = 1.4; SizeW_Y = 1.5;

						CenterB_X = 0; CenterB_Y = 0.05;
						SizeB_X = 1; SizeB_Y = 1;
						break;
					}
					//////////////////////////////////
					if (chess.tablero[i][j]->GetJugador() == Jugador::W) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05f , 0.02f);
						spriteReyB.setCenter(CenterW_X, CenterW_Y);
						spriteReyB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
						spriteReyB.draw();
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05f , -0.02f);
					}
					if (chess.tablero[i][j]->GetJugador() == Jugador::B) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spriteReyN.setCenter(CenterB_X, CenterB_Y);
						spriteReyN.setSize(SizeB_X, SizeB_Y);
						spriteReyN.draw();;
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					break;

				case D:
					switch (Estadoskin)
					{
					case 1:
						skin = "default";
						break;
					case 2:
						skin = "StarWars";
						CenterW_X = 0.05; CenterW_Y = 0.15;
						SizeW_X = 1; SizeW_Y = 1.2;

						CenterB_X = 0.15; CenterB_Y = 0.2;
						SizeB_X = 1.3; SizeB_Y = 1.3;
						break;
					case 3:
						skin = "AnimalCrossing";
						CenterW_X = 0; CenterW_Y = 0.05;
						SizeW_X = 1; SizeW_Y = 1;

						CenterB_X = -0.05; CenterB_Y = 0.06;
						SizeB_X = 0.9; SizeB_Y = 0.95;
						break;
					}
					///////////////////////////////////
					if (chess.tablero[i][j]->GetJugador() == Jugador::W) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spriteReinaB.setCenter(CenterW_X, CenterW_Y);
						spriteReinaB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
						spriteReinaB.draw();
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					if (chess.tablero[i][j]->GetJugador() == Jugador::B) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spriteReinaN.setCenter(CenterB_X, CenterB_Y);
						spriteReinaN.setSize(SizeB_X, SizeB_Y);
						spriteReinaN.draw();;
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					break;

				case C:
					switch (Estadoskin)
					{
					case 1:
						//skin = "default";
						break;
					case 2:
						//skin = "StarWars";
						CenterW_X = -0.05; CenterW_Y = -0.1;
						SizeW_X = 0.9; SizeW_Y = 0.9;

						CenterB_X = -0.05; CenterB_Y = 0.02;
						SizeB_X = 0.9; SizeB_Y = 0.95;
						break;
					case 3:
						//skin = "AnimalCrossing";
						CenterW_X = 0; CenterW_Y = 0.04;
						SizeW_X = 1; SizeW_Y = 1;

						CenterB_X = -0.05; CenterB_Y = 0.02;
						SizeB_X = 0.9; SizeB_Y = 0.95;
						break;
					}
					////////////////////////////////////
					if (chess.tablero[i][j]->GetJugador() == Jugador::W) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spriteCaballoB.setCenter(CenterW_X, CenterW_Y);
						spriteCaballoB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
						spriteCaballoB.draw();
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					if (chess.tablero[i][j]->GetJugador() == Jugador::B) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spriteCaballoN.setCenter(CenterB_X, CenterB_Y);
						spriteCaballoN.setSize(SizeB_X, SizeB_Y);
						spriteCaballoN.draw();;
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05, -0.02f);
					}
					break;

				case A:
					switch (Estadoskin)
					{
					case 1:
					//	skin = "default";

						break;
					case 2:
						//skin = "StarWars";
						CenterW_X = -0.05; CenterW_Y = 0.01;
						SizeW_X = 0.9; SizeW_Y = 0.9;

						CenterB_X = -0.1; CenterB_Y = 0.03;
						SizeB_X = 0.8; SizeB_Y = 0.9;
						break;
					case 3:
						//skin = "AnimalCrossing";
						CenterW_X = 0; CenterW_Y = 0.04;
						SizeW_X = 1; SizeW_Y = 1;

						CenterB_X = 0.15; CenterB_Y = 0.1;
						SizeB_X = 1.3; SizeB_Y = 1.2;
						break;
					}
					//////////////////////////////////
						if (chess.tablero[i][j]->GetJugador() == Jugador::W) {
							glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05, 0.02f);
							spriteAlfilB.setCenter(CenterW_X, CenterW_Y);
							spriteAlfilB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
							spriteAlfilB.draw();
							glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05, -0.02f);
						}
						if (chess.tablero[i][j]->GetJugador() == Jugador::B) {
							glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
							spriteAlfilN.setCenter(CenterB_X, CenterB_Y);
							spriteAlfilN.setSize(SizeB_X, SizeB_Y);
							spriteAlfilN.draw();;
							glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
						}
					break;

				case T:
					switch (Estadoskin)
					{
					case 1:
						//skin = "default";
						break;
					case 2:
						//skin = "StarWars";
						CenterW_X = -0.05; CenterW_Y = -0.01;
						SizeW_X = 0.9; SizeW_Y = 0.9;

						CenterB_X = -0.05; CenterB_Y = 0.06;
						SizeB_X = 0.9; SizeB_Y = 0.95;
						break;
					case 3:
						//skin = "AnimalCrossing";
						CenterW_X = 0; CenterW_Y = 0.05;
						SizeW_X = 1; SizeW_Y = 1;

						CenterB_X = -0.05; CenterB_Y = 0.06;
						SizeB_X = 0.9; SizeB_Y = 0.95;
						break;
					}
					/////////////////////////////////////
					if (chess.tablero[i][j]->GetJugador() == Jugador::W) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05, 0.02f);
						spriteTorreB.setCenter(CenterW_X, CenterW_Y);
						spriteTorreB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
						spriteTorreB.draw();
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					if (chess.tablero[i][j]->GetJugador() == Jugador::B) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spriteTorreN.setCenter(CenterB_X, CenterB_Y);
						spriteTorreN.setSize(SizeB_X, SizeB_Y);
						spriteTorreN.draw();;
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05, -0.02f);
					}
					break;

				case P:
					switch (Estadoskin)
					{
					case 1:
						//skin = "default";
						break;
					case 2:
						//skin = "StarWars";
						CenterW_X = 0.1; CenterW_Y = 0.03;
						CenterB_X = 0.05; CenterB_Y = 0.04;
						SizeW_X = 1.2; SizeW_Y = 0.97;
						SizeB_X = 1.1; SizeB_Y = 0.9;
						break;
					case 3:
						//skin = "AnimalCrossing";
						CenterW_X = 0; CenterW_Y = 0.02;
						CenterB_X = 0.15; CenterB_Y = 0.04;
						SizeW_X = 0.9; SizeW_Y = 0.9;
						SizeB_X = 1.3; SizeB_Y = 1;
						break;
					}
					///////////////////////////////////
					if (chess.tablero[i][j]->GetJugador() == Jugador::W) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spritePeonB.setCenter(CenterW_X, CenterW_Y);
						spritePeonB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
						spritePeonB.draw();
						glTranslatef((float) - chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					if (chess.tablero[i][j]->GetJugador() == Jugador::B) {
						glTranslatef((float)chess.tablero[i][j]->GetPosicion().y, (float)chess.tablero[i][j]->GetPosicion().x - 0.05 , 0.02f);
						spritePeonN.setCenter(CenterB_X, CenterB_Y);
						spritePeonN.setSize(SizeB_X, SizeB_Y);
						spritePeonN.draw();
						glTranslatef((float)-chess.tablero[i][j]->GetPosicion().y, (float)-chess.tablero[i][j]->GetPosicion().x + 0.05 , -0.02f);
					}
					break;

				default:
					break;

				}
			}
		}
	}
		glPopMatrix();

	
}

void GLTablero::dibujaCasillasPosibles(const std::vector<Vector2D>& movimientosPosibles, const Vector2D& v) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3ub(255,0,0);
	glTranslatef(v.y+0.5, v.x+0.5, 0.1);
	glutWireSphere(0.35, 10, 5);
	glTranslatef(-v.y-0.5, -v.x-0.5, 0.1);
	glEnd();
	for (auto& mov : movimientosPosibles) {
		// Color semitransparente
		glColor4f(1.0f,0.0f, 0.0f, 0.6f); //Compones RGBA //los rangos van de (0-1) alpha es para la transparencia
		glBegin(GL_QUADS);
		glVertex3f(mov.y, mov.x, 0.01f);
		glVertex3f(mov.y + 1, mov.x, 0.01f);
		glVertex3f(mov.y + 1, mov.x + 1, 0.01f);
		glVertex3f(mov.y, mov.x + 1, 0.01f);
		glEnd();
	}
	glDisable(GL_BLEND);
}
