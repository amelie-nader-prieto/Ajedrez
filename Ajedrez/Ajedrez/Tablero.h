#pragma once
#include "Casilla.h"

class Tablero
{
protected:
	vector<vector<Casilla>>tablero;
public:
	Tablero(int filas = ROWS, int columnas = COLUMNS); //constructor por defecto
	
	int size_rows();
	int size_columns();
	Casilla getCasilla(int, int);
	vector<Casilla>getFila(int);
	vector<Casilla>getColumna(int);
	vector<Casilla>getAdyacentes(int,int);
};
