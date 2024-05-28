#include "dama.h"
#include "pieza.h"

Dama::Dama(int fila, int columna,Jugador j) :
	Pieza(fila, columna, D,j) {
}

void Dama::dibuja(int Estadoskin) {
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
	direccionB = "bin/imagenes/" + skin + "/ReinaNegro.png";
	direccionW = "bin/imagenes/" + skin + "/ReinaBlanco.png";
	const char* rutaB = direccionB.c_str();
	const char* rutaW = direccionW.c_str();
	SpriteSequence spriteReinaN{ rutaB, 1 };
	SpriteSequence spriteReinaB{ rutaW, 1 };

	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteReinaB.setCenter(CenterW_X, CenterW_Y);
		spriteReinaB.setSize(SizeW_X, SizeW_Y);
		spriteReinaB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteReinaN.setCenter(CenterB_X, CenterB_Y);
		spriteReinaN.setSize(SizeB_X, SizeB_Y);
		//spriteReinaN.flip(true, true);
		spriteReinaN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}