#include "peon.h"
//#include "pieza.h" //no hace falta en el cpp, solo en el .h

Peon::Peon(int fila, int columna,Jugador j) :
	Pieza(fila, columna, P,j)
{
}

void Peon::dibuja(int Estadoskin) {

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
		CenterW_X = 0.1; CenterW_Y = 0.03;
		CenterB_X = 0.05; CenterB_Y = 0.04;
		SizeW_X = 1.2; SizeW_Y = 0.97;
		SizeB_X = 1.1; SizeB_Y = 0.9;
		break;
	case 3:
		skin = "AnimalCrossing";
		CenterW_X = 0; CenterW_Y = 0.02;
		CenterB_X = 0.15; CenterB_Y = 0.04;
		SizeW_X = 0.9; SizeW_Y = 0.9;
		SizeB_X = 1.3; SizeB_Y = 1;



		break;
	}
	direccionB = "bin/imagenes/" + skin + "/PeonNegro.png";
	direccionW = "bin/imagenes/" + skin + "/PeonBlanco.png";
	const char* rutaB = direccionB.c_str();
	const char* rutaW = direccionW.c_str();
	SpriteSequence spritePeonN{ rutaB, 1 };
	SpriteSequence spritePeonB{ rutaW, 1 };

	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spritePeonB.setCenter(CenterW_X, CenterW_Y);
		spritePeonB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
		spritePeonB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spritePeonN.setCenter(CenterB_X, CenterB_Y);
		spritePeonN.setSize(SizeB_X, SizeB_Y);
		//spritePeonN.flip(true, true);
		spritePeonN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}