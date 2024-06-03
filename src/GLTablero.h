#pragma once
#include "Casilla.h"
#include "ETSIDI.h"
#include "LogicaAjedrez.h" //la uso para omitir casillas fuera del tablero
#include "Tablero.h"


using ETSIDI::SpriteSequence;

//enums to eliminate dependency of glut
enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };

class GLTablero
{

public:
	float x_ojo, y_ojo, z_ojo;	
	bool activar_musica=true;
	//GLTablero() : x_ojo(5), y_ojo(5), z_ojo (17){}

public:

	Casilla cas{};
	Tablero chess; //Solo es una prueba// no eliminar
	std::vector<Vector2D> movimientosPosibles;

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
	void dibujaCasillasPosibles(const std::vector<Vector2D>&, const Vector2D&);




	void rotarOjo() {
		//float dist = sqrt((x_ojo - 5.0) * (x_ojo - 5.0) + (z_ojo - 0.0) * (z_ojo - 0.0));
		float dist = sqrt((x_ojo - 5.0) * (x_ojo - 5.0) + (y_ojo - 5.0) * (y_ojo -5.0));
		float theta = atan2(x_ojo - 5.0, y_ojo - 5.0);
		theta += 0.05;
		y_ojo = 5.0 + dist * cos(theta);
		x_ojo = 5.0 + dist * sin(theta);
	}

protected:
	//mouse	
	int xcell_sel=0, ycell_sel=0;			//cell selected with mouse

};

