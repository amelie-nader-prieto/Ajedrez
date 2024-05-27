#include "caballo.h"
//#include "pieza.h" //no hace falta

Caballo::Caballo(int fila, int columna,Jugador j) :
	Pieza(fila, columna, C,j) {

}
void Caballo::dibuja(int Estadoskin) {

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
		CenterW_X = -0.05; CenterW_Y = -0.1;
		SizeW_X = 0.9; SizeW_Y = 0.9;

		CenterB_X = -0.05; CenterB_Y = 0.02;
		SizeB_X = 0.9; SizeB_Y = 0.95;
		break;
	case 3:
		skin = "AnimalCrossing";
		CenterW_X = 0; CenterW_Y = 0.04;
		SizeW_X = 1; SizeW_Y = 1;

		CenterB_X = -0.05; CenterB_Y = 0.02;
		SizeB_X = 0.9; SizeB_Y = 0.95;



		break;
	}
	direccionB = "bin/imagenes/" + skin + "/CaballoNegro.png";
	direccionW = "bin/imagenes/" + skin + "/CaballoBlanco.png";
	const char* rutaB = direccionB.c_str();
	const char* rutaW = direccionW.c_str();
	SpriteSequence spriteCaballoN{ rutaB, 1 };
	SpriteSequence spriteCaballoB{ rutaW, 1 };


	if (jugador == Jugador::W) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila - 0.95, 0);
		spriteCaballoB.setCenter(CenterW_X, CenterW_Y);
		spriteCaballoB.setSize(SizeW_X, SizeW_Y); //Esto se va ajustando segun como se vea la imagen
		spriteCaballoB.draw();
		glTranslatef(-columna + 1, -fila + 0.95, 0);
		glEnable(GL_LIGHTING);
	}

	if (jugador == Jugador::B) {
		glDisable(GL_LIGHTING);
		glTranslatef(columna - 1, fila + 0.05 - 1, 0);
		spriteCaballoN.setCenter(CenterB_X, CenterB_Y);
		spriteCaballoN.setSize(SizeB_X, SizeB_Y);
		//spriteCaballoN.flip(true, true);
		spriteCaballoN.draw();
		glTranslatef(-columna + 1, -fila - 0.05 + 1, 0);
		glEnable(GL_LIGHTING);
	}
}

