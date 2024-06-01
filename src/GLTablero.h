#pragma once
#include "Casilla.h"
#include "ETSIDI.h"
#include "LogicaAjedrez.h" //la uso para omitir casillas fuera del tablero


#include "Tablero.h"

//#include "alfil.h"

using ETSIDI::SpriteSequence;

//enums to eliminate dependency of glut
enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };

class GLTablero
{
public:

	Casilla cas{};
	Tablero chess; //Solo es una prueba
	void init();
	void dibuja(const int&);

	float width = 1.0f; //ancho de la casilla
	void MouseButton(int x, int y, int button, bool down, Vector2D&, Vector2D&, bool&);
	void world2cell(double x, double y, int& cell_x, int& cell_y) {
		//world coordinates to cell
		cell_x = (int)( abs(y / width));
		cell_y = (int)(x / width) ;
	}

	void drawPieces(Tablero&, const int&);

protected:
	//mouse	
	int xcell_sel=0, ycell_sel=0;			//cell selected with mouse

};

