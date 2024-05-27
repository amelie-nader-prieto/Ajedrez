#include "alfil.h"
//#include "pieza.h" //no hace falta

Alfil::Alfil(int fila, int columna,Jugador j) :
	Pieza(fila, columna, A, j ) {

}
void Alfil::dibuja(int Estadoskin) {

	std::string skin = "default";
	std::string direccionW = "";
	std::string direccionB = "";
	double CenterW_X, CenterW_Y, CenterB_X, CenterB_Y;
	double SizeW_X, SizeW_Y, SizeB_X, SizeB_Y;

	switch (Estadoskin)
	{
	case 1:
		skin = "default";



		break;
	case 2:
		skin = "StarWars";
		CenterW_X = -0.05; CenterW_Y = 0.01;
		SizeW_X = 0.9; SizeW_Y = 0.9;

		CenterB_X = -0.1; CenterB_Y = 0.03;
		SizeB_X = 0.8; SizeB_Y = 0.9;
		break;
	case 3:
		skin = "AnimalCrossing";
		CenterW_X = 0; CenterW_Y = 0.04;
		SizeW_X = 1; SizeW_Y = 1;

		CenterB_X = 0.15; CenterB_Y = 0.1;
		SizeB_X = 1.3; SizeB_Y = 1.2;



		break;
	}
	direccionB = "bin/imagenes/" + skin + "/AlfilNegro.png";
	direccionW = "bin/imagenes/" + skin + "/AlfilBlanco.png";
	const char* rutaB = direccionB.c_str();
	const char* rutaW = direccionW.c_str();
	SpriteSequence spriteAlfilN{ rutaB, 1 };
	SpriteSequence spriteAlfilB{ rutaW, 1 };

	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteAlfilB.setCenter(CenterW_X, CenterW_Y);
		spriteAlfilB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
		spriteAlfilB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteAlfilN.setCenter(CenterB_X, CenterB_Y);
		spriteAlfilN.setSize(SizeB_X, SizeB_Y);
		//spriteAlfilN.flip(true, true);
		spriteAlfilN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}
