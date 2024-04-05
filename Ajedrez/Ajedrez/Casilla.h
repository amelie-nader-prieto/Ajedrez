#pragma once
#include "LogicaAjedrez.h"
#include <iostream>

class Casilla
{
protected:
	Color color;
	bool hay_pieza, hay_rey;
public:
	Casilla(Color); //constructor por defecto

	void print_color();
};

