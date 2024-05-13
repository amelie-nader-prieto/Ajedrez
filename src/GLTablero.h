#pragma once
#include "Casilla.h"
#include "ETSIDI.h"
#include "LogicaAjedrez.h"
#define FILA 10
#define COLUMNA 11

//enums to eliminate dependency of glut
enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };
enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

//clase que funciona como interfáz gráfica
//para mostrar el tablero y las piezas
class GLTablero
{
public:
	Casilla cas;
	void init();
	void dibuja();

	float width = 1.0f; //solo para prueba, despues eliminar es el ancho de la casilla
	void MouseButton(int x, int y, int button, bool down, bool sKey, bool ctrlKey);
	void world2cell(double x, double y, int& cell_x, int& cell_y) {
		//world coordinates to cell
		cell_x = (int)(1+abs(y / width));
		cell_y = (int)(1+x / width);
	}

protected:
	//mouse	
	int xcell_sel, ycell_sel;			//cell selected with mouse

	//mouse+special-keys combination state events 
	bool controlKey;
	bool shiftKey;
	bool leftButton;
	bool rightButton;
	bool midButton;
};

