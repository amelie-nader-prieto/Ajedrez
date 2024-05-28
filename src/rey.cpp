#include "rey.h"
#include "pieza.h"

Rey::Rey(int fila, int columna,Jugador j) :
	Pieza(fila, columna, R,j) {
}

void Rey::dibuja(int Estadoskin) {
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

		CenterB_X = 0; CenterB_Y = 0.05;
		SizeB_X = 1; SizeB_Y = 1;
		break;
	case 3:
		skin = "AnimalCrossing";
		CenterW_X = 0.15; CenterW_Y = 0.3;
		SizeW_X = 1.4; SizeW_Y = 1.5;

		CenterB_X = 0; CenterB_Y = 0.05;
		SizeB_X = 1; SizeB_Y = 1;



		break;
	}
	direccionB = "bin/imagenes/" + skin + "/ReyNegro.png";
	direccionW = "bin/imagenes/" + skin + "/ReyBlanco.png";
	const char* rutaB = direccionB.c_str();
	const char* rutaW = direccionW.c_str();
	SpriteSequence spriteReyN{ rutaB, 1 };
	SpriteSequence spriteReyB{ rutaW, 1 };

	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteReyB.setCenter(CenterW_X, CenterW_Y);
		spriteReyB.setSize(SizeW_X, SizeW_Y);
		spriteReyB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteReyN.setCenter(CenterB_X, CenterB_Y);
		spriteReyN.setSize(SizeB_X, SizeB_Y);
		//spriteReyN.flip(true, true);
		spriteReyN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}